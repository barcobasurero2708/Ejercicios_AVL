
#include <bits/stdc++.h>
using namespace std;

template<typename data_type>
struct AVL {

    struct TreeNode {
        int height;
        int cantidad;
        int size;
        data_type data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type data = data_type(), int height = 0,
                 TreeNode* left = nullptr,
                 TreeNode* right = nullptr)
            : height(height), cantidad(1), size(1),
              data(data), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() {
        root = nullptr;
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u->height;
    }

    int size(TreeNode* u) {
        return u == nullptr ? 0 : u->size;
    }

    int FB(TreeNode* u) {
        return h(u->left) - h(u->right);
    }

    void update(TreeNode* u) {
        u->height = 1 + max(h(u->left), h(u->right));
        u->size = size(u->left) + size(u->right) + u->cantidad;
    }

    TreeNode* rotate_left(TreeNode* u) {
        TreeNode* v = u->right;

        u->right = v->left;
        v->left = u;

        update(u);
        update(v);

        return v;
    }

    TreeNode* rotate_right(TreeNode* u) {
        TreeNode* v = u->left;

        u->left = v->right;
        v->right = u;

        update(u);
        update(v);

        return v;
    }

    TreeNode* rebalance(TreeNode* u) {
        if (u == nullptr) return nullptr;

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

    bool search(data_type key) {
        TreeNode* current = root;

        while (current != nullptr) {
            if (current->data == key) {
                return true;
            }

            if (key < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return false;
    }

    TreeNode* insert(TreeNode* u, data_type value) {
        if (u == nullptr) {
            return new TreeNode(value);
        }

        if (value == u->data) {
            u->cantidad++;
        } else if (value < u->data) {
            u->left = insert(u->left, value);
        } else {
            u->right = insert(u->right, value);
        }

        return rebalance(u);
    }

    void insert(data_type value) {
        root = insert(root, value);
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;

        while (u->left != nullptr) {
            u = u->left;
        }

        return u;
    }

    TreeNode* erase(TreeNode* u, const data_type& value) {
        if (u == nullptr) return nullptr;

        if (value < u->data) {
            u->left = erase(u->left, value);
        } else if (value > u->data) {
            u->right = erase(u->right, value);
        } else {
            if (u->cantidad > 1) {
                u->cantidad--;
                return rebalance(u);
            }
            if (u->left == nullptr || u->right == nullptr) {
                TreeNode* child =
                    (u->left != nullptr) ? u->left : u->right;

                delete u;
                return child;
            }
            TreeNode* successor = min_element(u->right);
            u->data = successor->data;
            u->cantidad = successor->cantidad;
            u->right = erase_completo(u->right, successor->data);
        }

        return rebalance(u);
    }

    TreeNode* erase_completo(TreeNode* u, const data_type& value) {
        if (u == nullptr) return nullptr;

        if (value < u->data) {
            u->left = erase_completo(u->left, value);
        } else if (value > u->data) {
            u->right = erase_completo(u->right, value);
        } else {
            if (u->left == nullptr || u->right == nullptr) {
                TreeNode* child =
                    (u->left != nullptr) ? u->left : u->right;

                delete u;
                return child;
            }

            TreeNode* successor = min_element(u->right);

            u->data = successor->data;
            u->cantidad = successor->cantidad;

            u->right = erase_completo(u->right, successor->data);
        }

        return rebalance(u);
    }

    void erase(data_type value) {
        root = erase(root, value);
    }

    int contar_hasta(TreeNode* u, data_type x) {
        if (u == nullptr) return 0;

        if (u->data > x) {
            return contar_hasta(u->left, x);
        }

        return size(u->left) + u->cantidad + contar_hasta(u->right, x);
    }


    int contar_en_rango(data_type l, data_type r) {
        return contar_hasta(root, r) - contar_menores(root, l);
    }

    int contar_menores(TreeNode* u, data_type x) {
        if (u == nullptr) return 0;
        if (u->data >= x) {
            return contar_menores(u->left, x);
        }
        return size(u->left) + u->cantidad + contar_menores(u->right, x);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int q;
    cin >> q;
    AVL<int> T;
    for (int i = 0; i < q; i++) {
        int op, x;
        cin >> op;
        if (op == 1) {
            cin >> x;
            T.insert(x);
        } else if (op == 2) {
            cin >> x;
            T.erase(x);
        } else if (op == 3) {
            int l, r;
            cin >> l >> r;
            cout << T.contar_en_rango(l, r) << '\n';
        }
    }
    return 0;
}
