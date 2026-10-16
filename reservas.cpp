
#include <bits/stdc++.h>
using namespace std;

struct AVL {
    struct TreeNode {
        int inicio;
        int fin;
        int height;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int inicio, int fin, int height = 0,
                TreeNode* left = nullptr,
                TreeNode* right = nullptr)
            : inicio(inicio), fin(fin), height(height),left(left), right(right) {}
    };

    TreeNode* root;

    AVL() {
        root = nullptr;
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u->height;
    }

    int FB(TreeNode* u) {
        return h(u->left) - h(u->right);
    }

    void update(TreeNode* u) {
        u->height = 1 + max(h(u->left), h(u->right));
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

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;

        while (u->left != nullptr) {
            u = u->left;
        }

        return u;
    }

    TreeNode* insert(TreeNode* u, int inicio, int fin) {
        if (u == nullptr) {
            return new TreeNode(inicio, fin);
        }

        if (inicio < u->inicio) {
            u->left = insert(u->left, inicio, fin);
        } else {
            u->right = insert(u->right, inicio, fin);
        }

        return rebalance(u);
    }

    TreeNode* erase(TreeNode* u, int inicio) {
        if (u == nullptr) return nullptr;
        if (inicio < u->inicio) {
            u->left = erase(u->left, inicio);
        } else if (inicio > u->inicio) {
            u->right = erase(u->right, inicio);
        } else {
            if (u->left == nullptr || u->right == nullptr) {
                TreeNode* child =(u->left != nullptr) ? u->left : u->right;
                delete u;
                return child;
            }
            TreeNode* successor = min_element(u->right);
            u->inicio = successor->inicio;
            u->fin = successor->fin;
            u->right = erase(u->right, successor->inicio);
        }

        return rebalance(u);
    }

    TreeNode* anterior(int s) {
        TreeNode* current = root;
        TreeNode* candidato = nullptr;

        while (current != nullptr) {
            if (current->inicio < s) {
                candidato = current;
                current = current->right;
            } else {
                current = current->left;
            }
        }

        return candidato;
    }

    TreeNode* siguiente(int s) {
        TreeNode* current = root;
        TreeNode* candidato = nullptr;

        while (current != nullptr) {
            if (current->inicio >= s) {
                candidato = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return candidato;
    }

    TreeNode* buscar_anterior_o_igual(int t) {
        TreeNode* current = root;
        TreeNode* candidato = nullptr;

        while (current != nullptr) {
            if (current->inicio <= t) {
                candidato = current;
                current = current->right;
            } else {
                current = current->left;
            }
        }

        return candidato;
    }

    bool reservar(int inicio, int fin) {
        TreeNode* ant = anterior(inicio);
        TreeNode* sig = siguiente(inicio);

        if (ant != nullptr && ant->fin > inicio) {
            return false;
        }

        if (sig != nullptr && sig->inicio < fin) {
            return false;
        }

        root = insert(root, inicio, fin);
        return true;
    }

    void consultar(int t) {
        TreeNode* candidato = buscar_anterior_o_igual(t);

        if (candidato != nullptr && t < candidato->fin) {
            cout << candidato->inicio << " "<< candidato->fin << '\n';
        } else {
            cout << "LIBRE\n";
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int q;
    cin >> q;
    AVL T;
    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int s, e;
            cin >> s >> e;
            if (T.reservar(s, e)) {
                cout << "SI\n";
            } else {
                cout << "NO\n";
            }
        } else if (op == 2) {
            int s;
            cin >> s;
            T.root = T.erase(T.root, s);
        } else if (op == 3) {
            int t;
            cin >> t;
            T.consultar(t);
        }
    }

    return 0;
}
