# Mini Arknights ncurses

Mô phỏng nhỏ Arknights chạy trong terminal sử dụng ncurses.

## Yêu cầu
- g++ (C++17)
- make
- ncurses (libncurses5-dev, libncursesw5-dev)
- nlohmann-json (header-only)

## Cài đặt thư viện (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install -y build-essential libncurses5-dev libncursesw5-dev nlohmann-json3-dev
```

## Biên dịch
```bash
make
```

## Chạy game
```bash
./ark_ncurses
```

## Windows

### Lựa chọn 1: WSL (Ubuntu) — khuyến nghị nếu muốn chạy trong terminal nhanh gọn
1) Cài WSL (PowerShell Admin):
```powershell
wsl --install -d Ubuntu
```
2) Trong Ubuntu (WSL), cài toolchain và thư viện:
```bash
sudo apt update
sudo apt install -y build-essential libncurses5-dev libncursesw5-dev nlohmann-json3-dev
```
3) Vào thư mục dự án và biên dịch/chạy:
```bash
cd /mnt/c/Users/DELL/projects/Vspack_project/arknights_vspack
make
./ark_ncurses
```

### Lựa chọn 2: MSYS2 (native Windows) — nếu muốn có .exe chạy trên Windows
1) Mở "MSYS2 UCRT64" shell, rồi cài toolchain và thư viện:
```bash
pacman -Syu --noconfirm
pacman -S --noconfirm mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make \
  mingw-w64-ucrt-x86_64-ncurses mingw-w64-ucrt-x86_64-nlohmann-json
```
2) Biên dịch và chạy:
```bash
cd /c/Users/DELL/projects/Vspack_project/arknights_vspack
mingw32-make
./ark_ncurses.exe
```

Lưu ý:
- Chạy từ đúng thư mục `arknights_vspack` để chương trình đọc được `operator.json` và `map.json`.
- Nếu gặp lỗi do phụ thuộc `json.hpp`: dự án dùng `#include <nlohmann/json.hpp>` (header-only). Hãy đảm bảo gói nlohmann-json đã được cài (trên Ubuntu: `nlohmann-json3-dev`, trên MSYS2: `mingw-w64-...-nlohmann-json`). Nếu cần, trong `makefile` hãy để target dạng `ark_ncurses: main.cpp` (không yêu cầu file `json.hpp`).

### Điều khiển
- Mũi tên: Di chuyển con trỏ
- p: Đặt operator
- o: Chuyển operator
- u: Nâng cấp operator tại vị trí con trỏ
- s: Lưu map
- l: Load map
- space: Gọi đợt quái mới
- q: Thoát
