#ifndef MIN_MAX_TREE_INCLUDED
#define MIN_MAX_TREE_INCLUDED

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class MinMaxTreeNode
{
    std::vector<MinMaxTreeNode<T>> _children;
    T                              _node_val;

    size_t _depth;
    int    _value;


    inline bool valCompare(const int, const int);
    inline bool valCompare(const int);

    inline bool calcNextLevel();

public:
    MinMaxTreeNode(T &&val, const int depth = 0);

    size_t validate_start(const size_t maxDepth);
    int    validate(const size_t maxDepth);
    int    validate(const size_t maxDepth, const int leftBranchVal);
    int    validate_full(const size_t maxDepth);

    // void calcNextLevel();

    void printTree(std::ostream &os, const size_t startDepth,
                   const bool printField = false);


    void cutTowardChild(const size_t childIndex);


    T &getNodeVal();
};



// Inline methods:
template <typename T>
bool MinMaxTreeNode<T>::valCompare(const int val, const int otherVal)
{
    if (_depth % 2) {
        return val > otherVal;
    } else {
        return val < otherVal;
    }
}

template <typename T>
bool MinMaxTreeNode<T>::valCompare(const int otherVal)
{
    return valCompare(_value, otherVal);
}



// Constructor:
template <typename T>
MinMaxTreeNode<T>::MinMaxTreeNode(T &&val, const int depth)
    : _node_val(val)
    , _depth(depth)
    , _value(0)
{}



// Public methods:
template <typename T>
size_t MinMaxTreeNode<T>::validate_start(const size_t maxDepth)
{
    if (_node_val.isLeaf() || (_children.size() == 0 && !calcNextLevel())) {
        _value = _node_val.evaluate();
        return 0;
    }

    auto iter           = _children.begin();
    _value              = iter->validate(maxDepth);
    size_t index        = 1;
    size_t currentIndex = 1;

    while (++iter < _children.end()) {
        ++currentIndex;
        int val = iter->validate(maxDepth, _value);

        if (valCompare(val)) {
            _value = val;
            index  = currentIndex;
        }
    }

    return index;
}


template <typename T>
int MinMaxTreeNode<T>::validate(const size_t maxDepth)
{
    if (_depth == maxDepth || _node_val.isLeaf()) {
        _value = _node_val.evaluate();
    } else {
        if (_children.size() == 0 && !calcNextLevel()) {
            _value = _node_val.evaluate();
            return _value;
        }

        auto iter = _children.begin();
        _value    = iter->validate(maxDepth);

        while (++iter < _children.end()) {
            int val = iter->validate(maxDepth, _value);
            if (valCompare(val)) {
                _value = val;
            }
        }
    }

    return _value;
}

template <typename T>
int MinMaxTreeNode<T>::validate(const size_t maxDepth, const int beta)
{
    if (_depth == maxDepth || _node_val.isLeaf()) {
        _value = _node_val.evaluate();
    } else {
        if (_children.size() == 0 && !calcNextLevel()) {
            _value = _node_val.evaluate();
            return _value;
        }

        auto iter = _children.begin();
        _value    = iter->validate(maxDepth);

        if (!valCompare(beta)) {
            return _value;
        }

        while (++iter < _children.end()) {
            int val = iter->validate(maxDepth, _value);

            if (!valCompare(val, beta)) {
                _value = val;
                return val;
            }

            if (valCompare(val)) {
                _value = val;
            }
        }
    }

    return _value;
}


template <typename T>
int MinMaxTreeNode<T>::validate_full(const size_t maxDepth)
{
    if (_depth == maxDepth || _node_val.isLeaf()) {
        _value = _node_val.evaluate();
    } else {
        if (_children.size() == 0 && !calcNextLevel()) {
            _value = _node_val.evaluate();
            return _value;
        }

        auto iter = _children.begin();
        _value    = iter->validate_full(maxDepth);

        while (++iter > _children.end()) {
            int val = iter->validate_full(maxDepth);

            if (valCompare(val)) {
                _value = val;
            }
        }
    }

    return _value;
}



template <typename T>
bool MinMaxTreeNode<T>::calcNextLevel()
{
    if (_node_val.isLeaf()) {
        return false;
    }

    auto children = _node_val.getNewLevel();
    if (children.size() == 0) {
        return false;
    }

    for (auto &child : children) {
        _children.push_back(MinMaxTreeNode(std::move(child), _depth + 1));
    }

    return true;
}



template <typename T>
T &MinMaxTreeNode<T>::getNodeVal()
{
    return _node_val;
}



// Helper functions:
template <typename T>
void MinMaxTreeNode<T>::printTree(std::ostream &os, const size_t startDepth,
                                  const bool printField)
{
    for (size_t i = startDepth; i < _depth; ++i) {
        os << "    ";
    }

    os << _value << '\n';
    if (printField && _children.size() == 0) {
        _node_val.printIt(os);
    }

    for (auto node : _children) {
        node.printTree(os, startDepth, printField);
    }
}


template <typename T>
void MinMaxTreeNode<T>::cutTowardChild(const size_t childIndex)
{
    if (_children.size() <= childIndex) {
        return;
    }

    _value    = _children[childIndex]._value;
    _node_val = _children[childIndex]._node_val;
    ++_depth;
    // std::vector<MinMaxTreeNode<T>> tempChildren =
    //     _children[childIndex]._children;
    // _children = tempChildren;
    std::vector<MinMaxTreeNode<T>> tempChildren =
        std::move(_children[childIndex]._children);
    _children = std::move(tempChildren);
}

#endif
