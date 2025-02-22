# Tên file chương trình đầu ra
TARGET = e-commerce-fcode

# Các file nguồn
SRC = main.c src/global.c src/login.c src/register.c helpers/function.c helpers/viewui.c

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
