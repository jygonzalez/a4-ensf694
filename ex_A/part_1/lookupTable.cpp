/**
 *  File Name: lookupTable.cpp
 *  Assignment: ENSF 694 Summer 2024 - Lab 4 Exercise A Part 1
 *  Created by: Mahmood Moussavi
 *  Completed by: Yael Gonzalez
 *  Submission Date: July 26, 2024
 */

#include "lookupTable.h"

LookupTable::LookupTable(const LookupTable &source)
{
    copy(source);
}

LookupTable &LookupTable::operator=(const LookupTable &rhs)
{
    if (this != &rhs)
    {
        destroy();
        copy(rhs);
    }

    return *this;
}

LookupTable::~LookupTable()
{
    destroy();
}

LookupTable &LookupTable::begin()
{
    cursorM = headM;
    return *this;
}

int LookupTable::size() const
{
    return sizeM;
}

int LookupTable::cursor_ok() const
{
    return cursorM != nullptr;
}

const int &LookupTable::cursor_key() const
{
    if (cursorM == nullptr)
    {
        cerr << "Cursor is pointing to null.";
    }

    return cursorM->pairM.key;
}

const Type &LookupTable::cursor_datum() const
{
    if (cursorM == nullptr)
    {
        cerr << "Cursor is pointing to null.";
    }

    return cursorM->pairM.datum;
}

void LookupTable::insert(const Pair &pairA)
{
    LT_Node *new_node = new LT_Node(pairA, nullptr);

    // Case 1: List is empty
    if (headM == nullptr)
    {
        headM = new_node;
        sizeM++;
    }
    // Case 2: First node's key is greater than new insert
    else if (pairA.key < headM->pairM.key)
    {
        new_node->nextM = headM;
        headM = new_node;
        sizeM++;
    }
    // Case 3: First node's key is equal to new insert
    else if (pairA.key == headM->pairM.key)
    {
        headM->pairM.datum = pairA.datum; // update datum only
        delete new_node;                  // delete unnecessary node
    }
    // Case 4: New insert to be added across the list (after first node)
    else
    {
        LT_Node *curr = headM;

        while (curr->nextM != nullptr && curr->nextM->pairM.key < pairA.key)
        {
            curr = curr->nextM;
        }

        if (curr->nextM != nullptr && curr->nextM->pairM.key == pairA.key)
        {
            curr->nextM->pairM.datum = pairA.datum; // update datum only
            delete new_node;                        // delete unnecessary node
        }
        else
        {
            new_node->nextM = curr->nextM;
            curr->nextM = new_node;
            sizeM++;
        }
    }

    cursorM = nullptr;
}

int LookupTable::remove(const int &keyA)
{
    // Case 1: List is empty
    if (headM == nullptr)
    {
        cerr << "List is empty." << endl;
        return 0;
    }

    LT_Node *curr = headM;
    LT_Node *prev = nullptr;
    int removed_key;

    // Case 2: Node to be removed is the first in the list
    if (headM->pairM.key == keyA)
    {
        headM = headM->nextM;
        removed_key = curr->pairM.key;
        delete curr;
        sizeM--;
        cursorM = nullptr;
        return removed_key;
    }

    // Case 3: Node to be removed is elsewhere in the list
    while (curr != nullptr && curr->pairM.key != keyA)
    {
        prev = curr;
        curr = curr->nextM;
    }

    if (curr == nullptr)
    {
        cerr << "Key not found." << endl;
        return 0;
    }

    prev->nextM = curr->nextM;
    removed_key = curr->pairM.key;
    delete curr;
    sizeM--;
    cursorM = nullptr;
    return removed_key;
}

void LookupTable::find(const int &keyA)
{
    for (LT_Node *curr = headM; curr != nullptr; curr = curr->nextM)
    {
        if (curr->pairM.key == keyA)
        {
            cursorM = curr;
            return;
        }
    }
    cursorM = nullptr;
}

void LookupTable::go_to_first()
{
    if (sizeM > 0)
    {
        cursorM = headM;
    }
}

void LookupTable::step_fwd()
{
    if (cursor_ok())
    {
        cursorM = cursorM->nextM;
    }
}

void LookupTable::make_empty()
{
    destroy();
    headM = nullptr;
    cursorM = nullptr;
    sizeM = 0;
}

void LookupTable::display() const
{
    if (headM == nullptr)
    {
        cerr << "List is empty.";
    }
    else
    {
        cout << " " << cursorM->pairM.key << " " << cursorM->pairM.datum << endl;
    }
}

bool LookupTable::isEmpty() const
{
    return headM == nullptr;
}

int *LookupTable::retrieve_at(int i)
{
    if (i < 0 || i >= sizeM)
    {
        cerr << "Index should be positive and less than " << sizeM << endl;
        return nullptr;
    }

    LT_Node *curr = headM;

    for (int j = 0; j < i; ++j)
    {
        curr = curr->nextM;
    }

    return &(curr->pairM.key);
}

void LookupTable::destroy()
{
    while (headM != nullptr)
    {
        LT_Node *temp = headM;
        headM = headM->nextM;
        delete temp;
    }
    cursorM = nullptr;
}

void LookupTable::copy(const LookupTable &source)
{
    if (source.headM == nullptr)
    {
        headM = nullptr;
        sizeM = 0;
        cursorM = nullptr;
        return;
    }

    headM = new LT_Node(source.headM->pairM, nullptr);
    LT_Node *srcNode = source.headM->nextM;
    LT_Node *thisNode = headM;

    while (srcNode != nullptr)
    {
        thisNode->nextM = new LT_Node(srcNode->pairM, nullptr);
        thisNode = thisNode->nextM;
        srcNode = srcNode->nextM;
    }

    sizeM = source.sizeM;

    if (source.cursorM != nullptr)
    {
        LT_Node *srcCursor = source.headM;
        LT_Node *newCursor = headM;

        while (srcCursor != source.cursorM)
        {
            srcCursor = srcCursor->nextM;
            newCursor = newCursor->nextM;
        }
        cursorM = newCursor;
    }
    else
    {
        cursorM = nullptr;
    }
}
