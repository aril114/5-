#ifndef BST_TREENODE_H
#define BST_TREENODE_H

// узел двоичного дерева
template <typename T>
class TreeNode {
private:
    // данные
    T data;
    // левый дочерний узел
    TreeNode* leftChild;
    // правый дочерний узел
    TreeNode* rightChild;


public:
    // задает данные узла
    void setData(T newData);
    // задает левый дочерний узел
    void setL(TreeNode* child);
    // задает правый дочерний узел
    void setR(TreeNode* child);
    // возвращает левый дочерний узел
    TreeNode *getL() const;
    // возвращает правый дочерний узел
    TreeNode *getR() const;
    // конструктор узла по данным
    TreeNode(T aData);
    // конструктор узла по данным и левому дочернему узлу
    TreeNode(T aData, TreeNode* aleftChild);
    // конструктор узла по данным, левому и правому дочерним узлам
    TreeNode(T aData, TreeNode* aleftChild, TreeNode* arightChild);
    // возвращает данные
    T getData() const;
    // возвращает, имеются ли у узла дочерние узлы
    bool hasChild() const;
};

// задает поле данных для узла бинарного дерева
template <typename T>
void TreeNode<T>::setData(T newData) {
    data = newData;
}

// поиск в бинарном дереве
template <typename T>
TreeNode<T>* btSearch(TreeNode<T>* root, T query) {
    if (root == nullptr) return nullptr;
    if (root->getData() == query) return root;

    TreeNode<T>* r = root->getR();
    TreeNode<T>* result = btSearch(r, query);
    if (result != nullptr) return result;

    TreeNode<T>* l = root->getL();
    return btSearch(l, query);
}

// поиск в бинарном дереве
template <typename T>
TreeNode<T>* btSearchParent(TreeNode<T>* query, TreeNode<T>* root) {
    if (root == nullptr) return nullptr;
    if (root->getL() == query) return root;
    if (root->getR() == query) return root;

    TreeNode<T>* r = root->getR();
    TreeNode<T>* result = btSearchParent(query, r);
    if (result != nullptr) return result;

    TreeNode<T>* l = root->getL();
    return btSearchParent(query, l);
}

// вычисляет высоту бинарного дерева
template <typename T>
int btHeight(TreeNode<T>* root) {
    if (root == nullptr) return 0;
    return 1 + std::max(btHeight(root->getL()), btHeight(root->getR()));
}

// добавляет новый узел в бинарное дерево поиска
// node - указатель на корень дерева, value - значение
template <typename T>
void addToBST(TreeNode<T> *node, T value) {
    T nodeData = node->getData();
    if (nodeData == value) return;
    else if (value < nodeData) {
        TreeNode<T>* childNode = node->getL();
        if (childNode == nullptr) node->setL(new TreeNode<T>(value));
        else addToBST(childNode, value);
    }
    else if (value > nodeData) {
        TreeNode<T>* childNode = node->getR();
        if (childNode == nullptr) node->setR(new TreeNode<T>(value));
        else addToBST(childNode, value);
    }
}

// объявление нового типа специальной функции
template <typename T>
using funcVoidTN = void(*)(TreeNode<T> *);

// в угловых скобках должно быть T, это T вставляется в строку на 3 строки выше
template <typename T>
void NRL(TreeNode<T>* node, funcVoidTN<T> func) {
    func(node); // вызываем функцию
    TreeNode<T>* r = node->getR();
    if (r != nullptr) NRL(r, func); // передаем указатель на функцию
    TreeNode<T>* l = node->getL();
    if (l != nullptr) NRL(l, func);
}

// задает левый дочерний узел
template <typename T>
void TreeNode<T>::setL(TreeNode<T>* child) {
    leftChild = child;
}

// задает правый дочерний узел
template <typename T>
void TreeNode<T>::setR(TreeNode<T>* child) {
    rightChild = child;
}

// возвращает левый дочерний узел
template <typename T>
TreeNode<T>* TreeNode<T>::getL() const {
    return leftChild;
}

// возвращает правый дочерний узел
template <typename T>
TreeNode<T>* TreeNode<T>::getR() const {
    return rightChild;
}

// конструктор узла по данным
template <typename T>
TreeNode<T>::TreeNode(T aData) {
    data = aData;
    leftChild = nullptr;
    rightChild = nullptr;
}

// конструктор узла по данным и левому дочернему узлу
template <typename T>
TreeNode<T>::TreeNode(T aData, TreeNode<T>* aleftChild) {
    data = aData;
    leftChild = aleftChild;
    rightChild = nullptr;
}

// конструктор узла по данным, левому и правому дочерним узлам
template <typename T>
TreeNode<T>::TreeNode(T aData, TreeNode<T>* aleftChild, TreeNode<T>* arightChild) {
    data = aData;
    leftChild = aleftChild;
    rightChild = arightChild;
}

// возвращает данные
template <typename T>
T TreeNode<T>::getData() const {
    return data;
}

// возвращает, имеются ли у узла дочерние узлы
template <typename T>
bool TreeNode<T>::hasChild() const {
    return this->getL() != nullptr || this->getR() != nullptr;
}

// очищает память, занятую деревом
template <typename T>
void delBt(TreeNode<T>* node) {
    TreeNode<T>* leftChild = node->getL();
    if (leftChild != nullptr) delBt(leftChild);
    TreeNode<T>* rightChild = node->getR();
    if (rightChild != nullptr) delBt(rightChild);
    delete node;
}

// копирует дерево
template <typename T>
TreeNode<T>* copyBt(TreeNode<T>* oldTreeRoot) {
    TreeNode<T> *newlptr, *newrptr, *newnode;

    if (oldTreeRoot == nullptr)
        return nullptr;

    newlptr = copyBt(oldTreeRoot->getL());
    newrptr = copyBt(oldTreeRoot->getR());

    newnode = new TreeNode<T>(oldTreeRoot->getData(), newlptr, newrptr);

    return newnode;
}

// делает массив из дерева
template <typename T>
T* btToArray(TreeNode<T>* root) {
    int size = btCount(root);
    T* array = new T[size];
    int index = 0;
    populateArray(root, array, index);
    return array;
}

// вспомогательная функция для заполнения массива
template <typename T>
void populateArray(TreeNode<T> *node, T *array, int &index) {
    TreeNode<T>* leftChild = node->getL();
    if (leftChild != nullptr) populateArray(leftChild, array, index);
    TreeNode<T>* rightChild = node->getR();
    if (rightChild != nullptr) populateArray(rightChild, array, index);
    array[index] = node->getData();
    index++; // поменять функцию чтобы элементы были отсортированы
}

// подсчет узлов в бинарном дереве
template <typename T>
int btCount(TreeNode<T>* root) {
    int size = 0;
    btCountMain(root, size);
    return size;
}

// увеличивает параметр size на число, равное количеству элементов дерева
template <typename T>
void btCountMain(TreeNode<T>* node, int &size) {
    TreeNode<T>* leftChild = node->getL();
    if (leftChild != nullptr) btCountMain(leftChild, size);
    TreeNode<T>* rightChild = node->getR();
    if (rightChild != nullptr) btCountMain(rightChild, size);
    size++;
}

// удаление узла из бинарного дерева
template <typename T>
void btRemove(TreeNode<T>* toRemove, TreeNode<T>* root) {
    if (toRemove == nullptr) throw std::invalid_argument("toRemove = nullptr");
    if (root == nullptr) throw std::invalid_argument("root = nullptr");
    // нет дочерних узлов
    if (toRemove->getL() == nullptr && toRemove->getR() == nullptr) {
        TreeNode<T>* parent = btSearchParent(toRemove, root);
        if (parent == nullptr)
            delete toRemove;
            // устанавливаем в nullptr дочерний элемент родителя удаляемого элемента, который прежде ссылался на удаляемый
        else {
            if (parent->getL() == toRemove) {
                parent->setL(nullptr);
            }
            else {
                parent->setR(nullptr);
            }
            delete toRemove;
        }
    }

        //один дочерний узел
    else if (toRemove->getL() == nullptr || toRemove->getR() == nullptr) {
        TreeNode<T>* childNode;
        // childNode - тот узел, который не является nullptr
        if (toRemove->getL() == nullptr)
            childNode = toRemove->getR();
        else
            childNode = toRemove->getL();

        TreeNode<T>* parent = btSearchParent(toRemove, root);
        if (parent == nullptr) {
            delete toRemove;
            return;
        }

        // у родителя дочерний узел устанавливается в дочерний узел удаляемого узла
        if (parent->getL() == toRemove) {
            parent->setL(childNode);
        }
        else {
            parent->setR(childNode);
        }
        delete toRemove;
    }

        //два дочерних узла
    else {
        // тот узел, который хотели удалить, меняем местами с его бОльшим узлом и удаляем бОльший узел
        TreeNode<T>* successor = succ(toRemove, root);
        toRemove->setData(successor->getData());
        btRemove(successor, root);
    }
}

// поиск следующего бОльшего узла
template <typename T>
TreeNode<T>* succ(TreeNode<T>* node, TreeNode<T>* root) {
    if (node == nullptr || root == nullptr)
        throw std::invalid_argument("Один или оба аргумента являются nullptr.");
    TreeNode<T>* result = node->getR();

    // правого потомка нет
    if (result == nullptr) {
        // node является корнем и он наибольший.
        // Возвращается nullptr
        if (root == node)
            return result;

        T nodeData = node->getData();
        TreeNode<T>* nd = root;
        T ndData = root->getData();

        TreeNode<T> *lCh, *rCh;

        // идем вверх до первого родительского узла справа
        while (true) {
            lCh = nd->getL();

            // проверяем левый узел, является ли он node
            if (lCh == node)
                return nd;

            rCh = nd->getR();

            // проверяем правый узел, является ли node он
            if (rCh == node)
                return result;

            // node находится слева. Переходим влево и запоминаем
            // текущий узел как последнего правого родителя
            if (nodeData < ndData) {
                result = nd;
                nd = lCh;
                ndData = nd->getData();
            }
                // node справа. Переходим вправо
            else {
                nd = rCh;
                ndData = nd->getData();
            }
        }
    }
    while (result -> getL() != nullptr)
        result = result->getL();
    return result;
}


#endif //BST_TREENODE_H
