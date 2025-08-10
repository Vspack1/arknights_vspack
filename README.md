# Mini Arknights ncurses

Mô phỏng nhỏ Arknights chạy trong terminal sử dụng ncurses.

## Yêu cầu
- g++ (C++17)
- make
- ncurses (libncurses5-dev, libncursesw5-dev)

## Cài đặt thư viện (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install g++ make libncurses5-dev libncursesw5-dev
```

## Biên dịch
```bash
make
```

## Chạy game
```bash
./ark_ncurses
```

### Điều khiển
- Mũi tên: Di chuyển con trỏ
- p: Đặt operator
- o: Chuyển operator
- u: Nâng cấp operator tại vị trí con trỏ
- s: Lưu map
- l: Load map
- space: Gọi đợt quái mới
- q: Thoát
