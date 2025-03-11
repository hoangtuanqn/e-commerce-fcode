#ifndef GLOBAL_H
#define GLOBAL_H
#define MAX_USERS 500 // LƯU TRỮ SỐ THÀNH VIÊN TỐI ĐA
#define MAX_CATEGORIES 1000 // LƯU TRỮ SỐ DANH MỤC TỐI ĐA
#define MAX_PRODUCTS 1000 // LỮU TRỮ SỐ SẢN PHẨM TỐI ĐA
#define MAX_CARTS 200 // SỐ TRỮ TRONG GIỎ HÀNG TỐI ĐA
#define MAX_ORDERS 200 // LƯU TRỮ SẢN PHẨM ĐÃ ĐẶT HÀNG
#define SHIPPING_FEE 5.00 // PHÍ VẬN CHUYỂN
typedef struct {
    char username[50];
    char password[50];
    char email[100];
    char phone[20];
    char full_name[100];
    char address[200];
    int account_type; // 1 = Buyer, 2 = Seller
    char shop_name[100];       // Only for sellers
    char warehouse_address[200]; // Only for sellers
    int id_cart; // không cần quan tâm cái này vì nó là chỉ mục giỏ hàng của người dùng này trong cart_data
    int id_list_user; // không cần quan tâm. Nó là chỉ mục trong biến list_user
} User;

typedef struct {
    char username[50];
    char category[100];
    int quantity_product;
} Category;
typedef struct {
    char username[50];
    char category[100];
    char name_product[2000];
    float price;
    int quantity;
    char description[2000];
    int status;
    int sold_quantity;
} Product;

typedef struct {
    char buyer[50]; // tên người mua
    int id_product[200]; // id mã đơn hàng
    int quantity_product[200]; // số lượng mua mỗi sản phẩm -> ứng với id_product
    int quantity; // Số lượng sản phẩm
} Cart;

typedef struct {
    char buyer[50]; // tên người mua
    char email[100];
    char phone[20];
    char full_name[100];
    char address[200];
    char order_id[8];
    char time_buy[200];
    int id_product[200];
    float shipping_fee; // phí giao hàng
    int quantity_product[200];
    char note_product[200][1000]; // note cho từng đơn hàng
    float total_product[200];
    float total;
    int quantity; // số lượng sản phẩm mua
    int status; // 0 - chờ xử lý, 1 - thành công, 2 - thất bại
} Order;

extern int is_logged_in;
extern int is_pause_program;
extern User current_user;
extern int counter_user; // lưu số lượng thành viên
extern User list_user[MAX_USERS]; // Sử dụng hằng số MAX_USERS

extern int counter_category_all;
extern int counter_product_all;
extern Category category_data[MAX_CATEGORIES];
extern Product product_data[MAX_PRODUCTS];
extern Cart cart_data[MAX_CARTS];
extern Order order_data[MAX_ORDERS];

extern int counter_category_seller;
extern int counter_product_seller;
extern int counter_cart_all; // số đơn hàng của người dùng
extern int counter_order_all;

#endif