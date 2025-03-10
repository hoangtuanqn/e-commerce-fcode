# Tên file chương trình đầu ra
TARGET = e-commerce-fcode

# Các file nguồn
SRC = main.c \
      src/global.c \
	  src/login.c \
	  src/register.c \
	  helpers/function.c \
	  helpers/view_ui.c \
	  src/seller/seller.c \
	  src/seller/global_seller.c \
	  src/seller/function_seller.c \
	  src/seller/view_add_category.c \
	  src/seller/view_ui.c \
	  src/seller/view_all_category.c \
	  src/seller/view_delete_category.c \
	  src/seller/view_update_category.c \
	  src/seller/view_all_product.c \
	  src/seller/view_add_product.c \
	  src/seller/view_update_product.c \
	  src/seller/view_delete_product.c \
	  src/seller/view_all_orders.c \
	  src/buyer/buyer.c \
	  src/buyer/view_ui.c \
	  src/buyer/view_browse_products.c \
	  src/buyer/view_add_to_cart.c \
	  src/buyer/view_all_cart.c \
	  src/buyer/view_check_out.c \
	  src/buyer/view_delete_cart.c \
	  src/buyer/view_search_products.c \
	  src/buyer/view_order_history.c \
	  src/buyer/view_change_password.c
	  
# Các file object
OBJ = $(SRC:.c=.o)

# Trình biên dịch
CC = gcc

# Cờ biên dịch
CFLAGS = -Wall -Wextra -g

# Quy tắc mặc định (tạo file thực thi)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Quy tắc biên dịch từng file .c thành .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Quy tắc dọn dẹp file object
clean:
	rm -f $(OBJ) $(TARGET)
