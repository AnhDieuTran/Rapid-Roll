# Rapid-Roll
## Trần Diệu Anh - 21020279

### 1. Hướng dẫn cài đặt
  - Chương trình sử dụng Visual Studio Code
  - Download file Rapid_Roll.rar về máy và giải nén.
  - Cách chạy chương trình:
    + Mở trên PowerShell window (Shift + chuột phải) // hoặc // Mở trong Visual Studio Code.
    + Gõ "mingw32-make" để make chương trình.
    + Gõ "main.exe" + ấn Tab (.\main.exe).
    + Game đã được chạy. 
 

**2. Mô tả chung về trò chơi**
  Người chơi di chuyển quả bóng bằng phím mũi tên trái để đi sang trái, và phím mũi phải để đi sang phải. Quả bóng phải đập vào thanh màu để thêm điểm và đi tiếp, nếu không, nếu nó va chạm với gai nhọn phía trên, rơi ra ngoài giới hạn dưới hoặc rơi trên cọc, người chơi sẽ mất 1 mạng. 
  Có thể thêm mạng khi ăn những icon trái tim. Có thêm chức năng bảo vệ khi rơi vào cọc khi ăn icon khiên bảo vệ.
  Mục tiêu của trò chơi là lăn bóng trong thời gian lâu hơn và ghi điểm cao hơn.

**3. Mô tả chức năng**


**4. Các kỹ thuật lập trình đã dùng**
  - Đồ hoạ bằng SDL2, SDL_image, SDL_ttf, SDL_mixer.
  - Sử dụng mảng Vector. 
  - Dùng cấu trúc Class cho Painter, bar, items.
  - Tách file, chia mã nguồn.
  - Con trỏ (ít)

**5. Kết luận**
  - Hướng phát triển thêm: Lập trình để game có đồ hoạ sinh động và đẹp hơn. Thêm các chức năng mới cho game sinh động. Chơi đối kháng giữa nhiều người...
  - Điều tâm đắc: Sau khi hoàn thiện game bước đầu, em 
