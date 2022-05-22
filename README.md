# Rapid-Roll
> Bài tập lớn lớp Lập trình nâng cao INT2215 1

> Sử dụng C ++, SDL2, SDL_ttf, SDL_image, SDL_mixer thư viện phát triển trên Visual Studio Code.
## Trần Diệu Anh - 21020279

### 1. Hướng dẫn cài đặt
	**a. Cài đặt**
		- Chương trình sử dụng Visual Studio Code
		- Tải xuống đầy đủ [VS Code](https://code.visualstudio.com/download)
		- Tải [MinGW-W64](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-win32/seh/x86_64-7.3.0-release-win32-seh-rt_v5-rev0.7z)
			* Giải nén file vừa tải			
			* Copy thư mục `mingw64` vào **<ROOTDIR>** (Ví dụ `D:\software`)
			* Cài đặt đường dẫn PATH đến **<ROOTDIR>\mingw64\bin**

			`💡 Kiểm tra bằng cách gọi `g++` và `mingw32-make` trong terminal`
		- Download file [Rapid_Roll.rar](https://github.com/AnhDieuTran/Rapid_Roll/raw/main/Rapid_Roll.rar) về máy và giải nén.

	**b. Cách chạy chương trình**
		* Cách 1: Ấn đúp chuột vào file `main.exe`
		* Cách 2: 
			+ Mở Folder `Rapid Roll` trong VS Code.
				+ Gõ **`mingw32-make`** + Enter để make chương trình trong Terminal.
				+ Gõ **`main.exe`** + ấn Tab (.\main.exe) + Enter
				+ Game đã được chạy. 
***
### 2. Mô tả chung về trò chơi
  Người chơi di chuyển quả bóng bằng phím mũi tên trái để đi sang trái, và phím mũi phải để đi sang phải. Quả bóng phải đập vào thanh màu để thêm điểm và đi tiếp, nếu không, nếu nó va chạm với gai nhọn phía trên, rơi ra ngoài giới hạn dưới hoặc rơi trên cọc, người chơi sẽ mất 1 mạng. 
  Có thể thêm mạng khi ăn những icon trái tim. Có thêm chức năng bảo vệ khi rơi vào cọc khi ăn icon khiên bảo vệ.
  Mục tiêu của trò chơi là lăn bóng trong thời gian lâu hơn và ghi điểm cao hơn.
***
### 3. Mô tả chức năng

***
### 4. Các kỹ thuật lập trình đã dùng
  - Đồ hoạ bằng SDL2, SDL_image, SDL_ttf, SDL_mixer.
  - Sử dụng mảng Vector. 
  - Dùng cấu trúc Class cho Painter, bar, items.
  - Tách file, chia mã nguồn.
  - Con trỏ (ít)
***
### 5. Kết luận
  - Hướng phát triển thêm: Lập trình để game có đồ hoạ sinh động và đẹp hơn. Thêm các chức năng mới cho game sinh động. Chơi đối kháng giữa nhiều người...
  - Điều tâm đắc: Sau khi hoàn thiện game bước đầu, em 
***
### 6. Nguồn tham khảo và tài nguyên game
