# Rapid-Roll
> Bài tập dự án cuối khoá lớp Lập trình nâng cao INT2215 1

> Sử dụng C ++, SDL2, SDL_ttf, SDL_image, SDL_mixer thư viện phát triển trên Visual Studio Code.
## Trần Diệu Anh - 21020279

### 1. Hướng dẫn cài đặt
**a. Cài đặt**
  - Chương trình sử dụng Visual Studio Code
  - Tải xuống đầy đủ [VS Code](https://code.visualstudio.com/download)
  - Tải các thư viện: [SDL2](https://www.libsdl.org/release/SDL2-devel-2.0.20-mingw.tar.gz), [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/)
  - Tải [MinGW-W64](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-win32/seh/x86_64-7.3.0-release-win32-seh-rt_v5-rev0.7z) 
     * Giải nén file vừa tải			
     * Copy thư mục `mingw64` vào **<ROOTDIR<Rootdir>>** (Ví dụ `D:\software`)
     * Cài đặt đường dẫn PATH đến **<ROOTDIR<Rootdir>>\mingw64\bin**

	`💡 Kiểm tra bằng cách gọi` **`g++`**` và `**`mingw32-make`**` trong terminal`
  - Download file [Rapid_Roll.rar](https://github.com/AnhDieuTran/Rapid_Roll/raw/main/Rapid_Roll.rar) về máy và giải nén.

**b. Cách chạy chương trình**
  * Cách 1: Ấn đúp chuột vào file `main.exe`
  * Cách 2: 
     + Mở Folder `Rapid Roll` trong VS Code.
     + Gõ **`mingw32-make`** + Enter để make chương trình trong Terminal.
     + Gõ **`main.exe`** + ấn Tab (.\main.exe) + Enter
     + Game đã được chạy. 
***
### 2. Mô tả chung về trò chơi, các ý tưởng chính
**a. Mô tả chung**
- Cách chơi: 
	+ Người chơi di chuyển quả bóng bằng phím mũi tên trái để đi sang trái, và phím mũi phải để đi sang phải. Quả bóng phải đập vào thanh màu để thêm điểm và đi tiếp, nếu không, nếu nó va chạm với gai nhọn phía trên, rơi ra ngoài giới hạn dưới hoặc rơi trên cọc, người chơi sẽ mất 1 mạng. 
	+ Có thể thêm mạng khi ăn những icon trái tim. Có thêm chức năng bảo vệ khi rơi vào cọc khi ăn icon khiên bảo vệ.
	+ Mục tiêu của trò chơi là lăn bóng trong thời gian lâu hơn và ghi điểm cao hơn.
	
**b. Các ý tưởng chính**
* Hệ thống Menu chọn độ khó, chơi game, chơi lại.
* Hệ thống các thanh bar, heart, shield.
* Hệ thống âm thanh.
* Đồ hoạ SDL2.
***
### 3. Mô tả chức năng
* Màn hình Menu:
	* Bắt đầu vào game bằng ấn nút Play.
	* Có 2 cách tắt chương trình: sử dụng nút tắt ở cửa sổ hoặc nút Exit ở Menu.
	* Khi con trỏ chuột chỉ vào chữ thì chữ chuyển màu đỏ.
* Màn hình chọn độ khó:
	* Có 3 mức độ chơi: Dễ, Trung Bình và Khó tương ứng với tốc độ di chuyển của các thanh màu.
* Màn hình chơi:
	* Bóng: Do người chơi điều khiển bằng mũi tên trái/phải từ bàn phím.
	* Các thanh màu, và thanh gai nhọn xuất hiện.
	* Số điểm đang có và số mạng ở hai góc trên phía trên màn hình.
	* Có các trái tim để tăng thêm mạng sống.
	* Có các tấm khiên để bảo vệ khỏi những thanh gai trong một thời gian nhất định.
* Màn hình kết thúc game:
	* Hiển thị số điểm chơi. 
	* Hiển thị top 5 điểm cao nhất.
	* Có thể thực hiện 2 thao tác:
		* Ấn nút PlayAgain để chơi lại ván mới.
		* Ấn nút Exit để thoát game.
* Video minh hoạ: [Rapid Roll]()
***
### 4. Các kỹ thuật lập trình đã dùng
  * Đồ hoạ bằng SDL2, SDL_image, SDL_ttf, SDL_mixer.
  * Sử dụng mảng Vector. 
  * Dùng cấu trúc Class cho Painter, bar, items.
  * Tách file, chia mã nguồn.
  * Một số kỹ thuật khác như: con trỏ, tạo vị trí ngẫu nhiên, vòng lặp game loop, ...  
***
### 5. Kết luận, hướng phát triển và các điều tâm đắc
  * Kết luận: Đây là game đầu tay tự làm nên vẫn còn đơn giản, có nhiều sai sót, code vẫn còn xấu, chưa được clean tối ưu nhất, khi chạy còn chiếm khá nhiều bộ nhớ. Thi thoảng có phát sinh lỗi.
  * Hướng phát triển thêm: 
	* Tối ưu hoá code game tốt nhất có thể.
	* Lập trình để game có đồ hoạ, âm thanh sinh động và đẹp hơn. 
	* Thêm các chức năng mới cho game: 
		* Hỏi tên người chơi và lưu tên trên bảng xếp hạng điểm cao vào file txt.
		* Hai người cùng chơi đối kháng trên một máy.
		* Chọn nhân vật chơi theo ý muốn.
		* Có thể thêm các items với chức năng mới.
  * Điều tâm đắc: 
	* Thông qua bài tập dự án này, em đã học thêm được rất nhiều điều về các kỹ thuật lập trình của ngôn ngữ C++, biết cách sử dụng thư viện đồ hoạ SDL2 để tạo một game có đồ hoạ và âm thanh, và phần nào đó nâng cao kỹ thuật của bản thân dù vẫn chưa hiểu được hết các lĩnh vực này.
	* Hiểu về tiến trình tạo và vận hành của một game.
	* Rút ra được nhiều kinh nghiệm, ngày càng yêu thích và thấy lập trình có rất nhiều thứ thú vị và hấp dẫn. Em cảm thấy rất vui và thích thú khi một đoạn code nào đó hoạt động theo ý muốn hay fix được một bug gì đó.
	* Đặc biệt qua quá trình làm project, gặp nhiều lỗi, em thấy bản thân cần phải thật kiên nhẫn, tỉ mỉ, biết tự học, chủ động tìm hiểu thêm bên ngoài, đồng thời sắp xếp, quản lý thời gian khoa học nhất. 
	
  * Em rất mong được các thầy cô chỉ dẫn nhiều hơn trong những quá trình học sau này để ngày một phát triển hơn.
***
### 6. Nguồn tham khảo
* Các hình ảnh trong game được lấy một phần từ google, một phần tự làm bằng [Canva](https://www.canva.com/)
* Âm thanh được lấy từ nhiều nguồn trên google
* Học về SDL/SDL2 tại [LT SDL](https://phattrienphanmem123az.com/lap-trinh-game-cpp), [LT SDL2](https://phattrienphanmem123az.com/lap-trinh-game-c-p2) và trên [Lazy Foo](https://lazyfoo.net/tutorials/SDL/index.php)
