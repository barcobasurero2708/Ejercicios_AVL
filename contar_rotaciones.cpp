
#include <iostream>
#include <algorithm>
using namespace std;

template<typename data_type>
struct AVL {
    struct TreeNode {
        int height;
        data_type data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type data = data_type(), int height = 0,
                    TreeNode* left = nullptr,
                    TreeNode* right = nullptr) :
                    data(data), height(height), left(left), right(right) {}
    };

    TreeNode* root;
    int rotaciones = 0;

    AVL() : root(nullptr) {}

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u->height;
    }

    void update(TreeNode* u) {
        u->height = 1 + max(h(u->left), h(u->right));
    }

    int FB(TreeNode* u) {
        return h(u->left) - h(u->right);
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;

        TreeNode* current = u;
        while (current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    TreeNode* rotate_left(TreeNode* u) {
        TreeNode* v = u->right;

        u->right = v->left;
        v->left = u;

        update(u);
        update(v);

        rotaciones++;
        return v;
    }

    TreeNode* rotate_right(TreeNode* u) {
        TreeNode* v = u->left;

        u->left = v->right;
        v->right = u;

        update(u);
        update(v);

        rotaciones++;
        return v;
    }

    TreeNode* rebalance(TreeNode* u) {
        update(u);

        if (FB(u) > 1) {
            if (FB(u->left) < 0) {
                u->left = rotate_left(u->left);
            }
            return rotate_right(u);
        }

        if (FB(u) < -1) {
            if (FB(u->right) > 0) {
                u->right = rotate_right(u->right);
            }
            return rotate_left(u);
        }

        return u;
    }

    TreeNode* insert(TreeNode* u, const data_type& value) {
        if (u == nullptr) {
            return new TreeNode(value);
        }

        if (value < u->data) {
            u->left = insert(u->left, value);
        } else {
            u->right = insert(u->right, value);
        }

        return rebalance(u);
    }

    TreeNode* erase(TreeNode* u, const data_type& value) {
        if (u == nullptr) {
            return nullptr;
        }

        if (value < u->data) {
            u->left = erase(u->left, value);
        } else if (u->data < value) {
            u->right = erase(u->right, value);
        } else {
            if (u->left == nullptr || u->right == nullptr) {
                TreeNode* child;

                if (u->left != nullptr) {
                    child = u->left;
                } else {
                    child = u->right;
                }

                delete u;
                return child;
            }

            TreeNode* successor = min_element(u->right);
            u->data = successor->data;
            u->right = erase(u->right, successor->data);
        }

        return rebalance(u);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    AVL<int> T;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int op, x;
        cin >> op >> x;

        T.rotaciones = 0;

        if (op == 1) {
            T.root = T.insert(T.root, x);
        } else if (op == 2) {
            T.root = T.erase(T.root, x);
        }

        cout << T.rotaciones << " " << T.h(T.root) << '\n';
    }

    return 0;
}