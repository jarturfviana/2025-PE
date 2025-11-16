#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTS 200
#define NAME_LEN 64

typedef struct {
    int code;
    char name[NAME_LEN];
    double price;
    int quantity;
} Product;

int load_products(const char *filename, Product products[], int max);
void print_menu(void);
void list_products(Product products[], int n);
int find_product(Product products[], int n, int code);
int add_product(Product products[], int *n, int max);
void sort_by_price_ascending(Product products[], int n);
int compare_price(const void *a, const void *b);
void print_product(const Product *p);
void clear_input_line(void);

int main(int argc, char *argv[]) {
    Product products[MAX_PRODUCTS];
    int n = 0;
    char filename[256];

    if (argc >= 2) {
        strncpy(filename, argv[1], sizeof(filename)-1);
        filename[sizeof(filename)-1] = '\0';
    } else {
        printf("Por favor, digite: produtos.txt     : ");
        if (scanf("%255s", filename) != 1) {
            fprintf(stderr, "Não existe arquivo com esse nome... (•́ ᴖ`•̀) \n");
            return 1;
        }
    }

    n = load_products(filename, products, MAX_PRODUCTS);
    printf("%d produtos carregados do arquivo \"%s\".\n\n ૮₍ ˶ᵔ ᵕ ᵔ˶ ₎ა", n, filename);

    int option = 0;
    do {
        print_menu();
        printf("Escolha uma opção: ");
        if (scanf("%d", &option) != 1) {
            printf("Entrada inválida. Tente novamente...\n");
            clear_input_line();
            continue;
        }
        clear_input_line();

        switch (option) {
            case 1:
                if (add_product(products, &n, MAX_PRODUCTS)) {
                    printf("Produto adicionado com sucesso! Total de produtos agora é %d\n d-(´▽｀)-b", n);
                }
                break;
            case 2: {
                int code;
                printf("Digite o código do produto a buscar: ");
                if (scanf("%d", &code) != 1) {
                    printf("Não existe produto com esse código... ( ╹ -╹)? \n");
                    clear_input_line();
                    break;
                }
                clear_input_line();
                int idx = find_product(products, n, code);
                if (idx >= 0) {
                    printf("Produto encontrado:\n");
                    print_product(&products[idx]);
                } else {
                    printf("Produto de código %d não encontrado. (╭ರ_•́)   \n", code);
                }
                break;
            }
            case 3:
                list_products(products, n);
                break;
            case 4:
                sort_by_price_ascending(products, n);
                printf("Produtos ordenados por preço (crescente):\n");
                list_products(products, n);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida, Tente novamente!\n");
        }
        printf("\n");
    } while (option != 5);

    return 0;
}

int load_products(const char *filename, Product products[], int max) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Não foi possível abrir esse arquivo '%s' ( ꩜ ᯅ ꩜;). Verifique se ele existe.\n", filename);
        return 0;
    }

    int count = 0;
    while (count < max) {
        int code;
        char name[NAME_LEN];
        double price;
        int qty;

        // Tenta ler quatro campos: código - nome - preço - quantidade
        int read = fscanf(fp, "%d %63s %lf %d", &code, name, &price, &qty);
        if (read == EOF || read == 0) break;
        if (read != 4) {
            
            char buffer[256];
            fgets(buffer, sizeof(buffer), fp);
            continue;
        }

        products[count].code = code;
        strncpy(products[count].name, name, NAME_LEN-1);
        products[count].name[NAME_LEN-1] = '\0';
        products[count].price = price;
        products[count].quantity = qty;
        count++;
    }

    fclose(fp);
    return count;
}

void print_menu(void) {
    printf("Menu:\n");
    printf("1 - Adicionar produto\n");
    printf("2 - Buscar produto por código\n");
    printf("3 - Imprimir produtos\n");
    printf("4 - Ordenar por preço e imprimir\n");
    printf("5 - Sair\n");
}

void list_products(Product products[], int n) {
    if (n == 0) {
        printf("Nenhum produto para mostrar.\n");
        return;
    }
    printf("%-6s %-20s %-10s %-10s\n", "Código", "Nome", "Preço", "Quantidade");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < n; ++i) {
        printf("%-6d %-20s R$ %-8.2f %-10d\n", products[i].code, products[i].name, products[i].price, products[i].quantity);
    }
}

int find_product(Product products[], int n, int code) {
    for (int i = 0; i < n; ++i) {
        if (products[i].code == code) return i;
    }
    return -1;
}

int add_product(Product products[], int *n, int max) {
    if (*n >= max) {
        printf("Impossível adicionar: capacidade máxima atingida.\n");
        return 0;
    }
    int code;
    char name[NAME_LEN];
    double price;
    int qty;

    printf("Novo produto - digite os dados solicitados.\n");
    printf("Código (inteiro): ");
    if (scanf("%d", &code) != 1) {
        printf("Código inválido.\n");
        clear_input_line();
        return 0;
    }
    clear_input_line();

    if (find_product(products, *n, code) >= 0) {
        printf("Já existe um produto com o código %d...\n", code);
        return 0;
    }

    printf("Nome: ");
    // lê uma linha completa (e aceita espaços)
    if (!fgets(name, sizeof(name), stdin)) {
        printf("Erro ao ler nome.\n");
        return 0;
    }
    
    size_t ln = strlen(name);
    if (ln > 0 && name[ln-1] == '\n') name[ln-1] = '\0';

    printf("Preço (ex: 9.90): ");
    if (scanf("%lf", &price) != 1) {
        printf("Preço inválido.\n");
        clear_input_line();
        return 0;
    }
    clear_input_line();

    printf("Quantidade (inteiro): ");
    if (scanf("%d", &qty) != 1) {
        printf("Quantidade inválida.\n");
        clear_input_line();
        return 0;
    }
    clear_input_line();

    products[*n].code = code;
    strncpy(products[*n].name, name, NAME_LEN-1);
    products[*n].name[NAME_LEN-1] = '\0';
    products[*n].price = price;
    products[*n].quantity = qty;
    (*n)++;
    return 1;
}

void sort_by_price_ascending(Product products[], int n) {
    qsort(products, (size_t)n, sizeof(Product), compare_price);
}

int compare_price(const void *a, const void *b) {
    const Product *pa = (const Product *)a;
    const Product *pb = (const Product *)b;
    if (pa->price < pb->price) return -1;
    if (pa->price > pb->price) return 1;
    return 0;
}

void print_product(const Product *p) {
    printf("Código: %d\n", p->code);
    printf("Nome: %s\n", p->name);
    printf("Preço: R$ %.2f\n", p->price);
    printf("Quantidade: %d\n", p->quantity);
}

void clear_input_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

