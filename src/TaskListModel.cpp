#include "TaskListModel.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QSet>

TaskListModel::TaskListModel(QObject *parent) :
    QAbstractListModel(parent),
    contents()
{

}

int TaskListModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return contents.size();
    else
        return 0;
}

QVariant TaskListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() >= contents.size() && role == Qt::DisplayRole) {
        return QVariant(contents[index.row()]->text());
    } else {
        return QVariant();
    }
}

void TaskListModel::mergeFrom(QList<QJsonValue*> src) {

    // Step 1: compute the longest common subsequence
    int smax = src.length(), dmax = contents.size();
    // The contents of this array use the bottom two bits to store
    // the direction in the matrix to the previous element.
    // for the item at [s][d],
    // 0 indicates end of sequence
    // 1 indicates that src[s] is not in the LCS
    // 2 indicates that dest[d] os not in the LCS
    // 3 indicates that src[s] = dest[d], and should be kept
    // TODO: Make this use less memory
    // TODO: Do we want to allocate this on the heap?

#define LCSIDX(s,d) ((d)+(s)*dmax)
    unsigned int *lcsmatrix = new unsigned int[(smax+1)*(dmax+1)];

    int src_it = 0, dst_it = 0;
    for (src_it = 0; src_it < smax; src_it++) {
        QString srcid = src[src_it]->toObject()["id"].toString();
        for (dst_it = 0; dst_it < dmax; dst_it++) {
            QString dstid = contents[dst_it]->id();
            if (srcid == dstid) {
                lcsmatrix[LCSIDX(src_it+1,dst_it+1)] =
                        (lcsmatrix[LCSIDX(src_it,dst_it)] & ~3) + 4 + 3; // 4 to increase link count, 3 for tag
            } else if (lcsmatrix[LCSIDX(src_it,dst_it+1)]
                       >= lcsmatrix[LCSIDX(src_it+1, dst_it)]) {
                lcsmatrix[LCSIDX(src_it+1,dst_it+1)] =
                        (lcsmatrix[LCSIDX(src_it,dst_it+1)] & ~3) + 1;
            } else {
                lcsmatrix[LCSIDX(src_it+1,dst_it+1)] =
                        (lcsmatrix[LCSIDX(src_it+1,dst_it)] & ~3) + 2;
            }
        }
    }

    // step 2: walk back along the matrix to remove the appropriate set of items from the list
    src_it = smax;
    dst_it = dmax;
    QModelIndex nullIdx = QModelIndex();
    while ((lcsmatrix[LCSIDX(src_it,dst_it)] & 3) != 0) {
        switch(lcsmatrix[LCSIDX(src_it,dst_it)] & 3) {
        case 0:
            break;
        case 1:
            src_it--;
            break;
        case 2: {
                beginRemoveRows(nullIdx, dst_it-1, dst_it-1);
                HrpgTask* obj = contents[dst_it-1];
                contents.remove(dst_it-1); // TODO: leak?
                delete obj;
                endRemoveRows();
            }
            dst_it--;
            break;
        case 3:
            src_it--;
            dst_it--;
            break;
        }
    }

    delete[] lcsmatrix;
    lcsmatrix=NULL;
#undef LCSIDX
    // Step 3: Insert new nodes...
    dst_it = 0;
    for (auto it = src.begin(); it != src.end(); ++it) {
        QString id = (*it)->toObject()["id"].toString();
        if (id.isNull())
            continue;

        if(contents[dst_it]->id() != id) {
            beginInsertRows(nullIdx, dst_it, dst_it);
            contents.insert(dst_it, HrpgTask::fromJSON(this, **it));
            endInsertRows();
        }
        dst_it++;
    }

}
