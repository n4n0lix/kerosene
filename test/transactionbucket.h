#pragma once

#include "_global.h"

class TransactionBucket {
    void        commit();
    TOKEN       write(vector<OBJECT>*);
    void        remove(TOKEN);

    void        commit_write(TOKEN, vector<OBJECT>*);
    void        commit_remove(TOKEN);
};