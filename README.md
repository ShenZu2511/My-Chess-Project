# MyChessProject

1. Hướng dẫn cài đặt: (vào CodeBlock)
	- Cài đặt thư viện SDL2 và SDL2 image vào project : Mở project, chuột phải project -> build option
	+ linker setting->other linker setting: thêm dòng lệnh sau -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	+ search directory->Compiler rồi add link dẫn tới ...\src\include\SDL2 và ...\src\sdl2imageinclude
	+ search directory->Linker rồi add link dẫn tới ...\src\lib và ...\src\sdl2imagelib
	
	- Chỉ để chạy chương trình thì vào bin->chạy file exe trong Release là được
	
2. Mô tả chung về trò chơi:
	- Game cờ vua cơ bản có chế độ đánh với máy cơ bản và chế độ 2 người chơi
	- Có thông tin game và bảng chức năng hỗ trợ để xoay bàn cờ, bắt đầu lại,đi lại,quay trở lại
	
	- Logic của game và kĩ thuật lập trình sử dụng để xây dựng chúng:
		+ Tốt thì khi ở vị trí bắt đầu đi được nhiều nhất 2 ô nếu không bị cản trên đường đi ; không ở vị trí bắt đầu chỉ đi được 1 ô thẳng lên trước nếu ô đó trống; có thể đi được và ô của địch khi ô đó chéo hướng lên trên theo hướng phe quân ta
		thêm vào đó tốt còn có thể phong hậu khi đi tới cuối bàn cờ và bắt tốt qua đường (3 luật đặc biệt của tốt)
			++ Xây dựng các nước mà tốt có thể đi ta phải tạo 1 hàm mà sử dụng các biến board(lưu trạng thái bàn cờ),flip(lưu trạng thái quay bàn)(gây phức tạp khi nhận biết sự tương đối của 2 bên hay đi tới cuối là ở đâu)
		+ Mã thì đi chữ L 
			++ Xây dựng các nước đi được bằng cách gọi 8 vị trí đó ra và kiểm tra có nằm trong bàn cờ? có quân nào phe gì ở đó hay không?
		+ Tượng đi chéo về 4 hướng và nếu bị chặn trên đường đi thì không đi tiếp được các ô chéo đằng sau đó nữa
			++ Xây dựng nước đi bằng cách sử dụng hàm while 4 lần cho 4 hướng, thêm vào đó xác định ô cuối cùng là phe nào xem có đi được vào không
		+ Xe đi ngang dọc về 4 hướng và nếu bị chặn trên đường thì k thể đi các ô còn lại
			++ Xây dựng xe tương tự như tượng dùng while về 4 hướng và xét ô chặn
		+ Hậu đi ngang dọc chéo và cũng bị chặn thì không thể đi các ô còn lại
			++ Xây dựng hậu nhờ kết hợp xe và tượng
		+ Vua thì chỉ việc xe cả 8 ô xung quanh nếu nằm trong bàn cờ và là khoảng trống hoặc quân địch thì có thể đi được
		
		***đây chỉ là hàm xây dựng các ô đi được cơ bản cho quân cờ trong struct ChessPiece vì để quân cờ có thể đi được thì còn liên quan đến nước đi có hợp lệ hay không? nghĩa là khi đi xong thì vua phe mình không được phép bị chiếu
	
	
		+ Các quy luật đặc biệt như nhập thành (vua xe cùng đi khi vua và xe hướng nhập thành chưa đi lần nào),phong hậu,bắt tốt qua sông được xử lí bằng các hàm nằm trong ChessMove và Move 
	
	- Ưu điểm:
		+ Hầu như đầy đủ logic của game cờ vua chỉ thiếu việc nhận biết hòa cờ, và điều kiện nhập thành không bị tướng địch giữ chân bị lỗi

		
	- Nhược điểm:
		+ Lúc chạy chế độ 2 người chơi thì vẫn có 1 số bug làm cho truy cập vào nơi không cho phép làm ngắt chương trình
		+ Cách xây dựng làm cho trạng thái cờ dễ hiểu hơn nhưng lại tốn nhiều dữ liệu nên không thích hợp dùng khi tạo AI
		+ Cũng vì vậy mà AI còn yếu, không thể áp thuật toán vào với cấu trúc trạng thái trò chơi phức tạp nhiều dữ kiện nhanh gây tràn bộ nhớ
		+ AI không có khả năng tự đi các nước cờ đặc biệt như nhập thành hay bắt tốt qua sông, vẫn có khả năng phong hậu
	
3. Mô tả chức năng đã cài đặt:
	- Bắt đầu game là 1 cái menu có 3 icon:
		+ Info icon: đưa ta đến thông tin game và ấn back để quay lại menu chính
		+ AI icon: chơi cờ với máy
		+ 2P: chơi cờ 2 người chơi
	
	- Bên trong chế độ 2 người chơi và cả chế độ chơi với AI ta đều có các tiện ích:
		+ Undo: quay lại nước cờ cũ dựa vào History của game 
		+ Restart: đưa bàn cờ trở về trạng thái đầu nhờ hàm Game::restart() thay đổi tất cả thông số về ban đầu
		+ Back: restart game và đưa về menu chính
		
	- Khi đi 1 nước chiếu đối thủ thì hiện cửa sổ thông báo check
	- Khi CheckMate thì sẽ hiện thông báo CheckMate và báo người chơi thắng, sau đó ấn R để Restart game
	(chức năng đang bị lỗi chỉ sử dụng được ở 1 phe nên tạm bỏ ra)

4. Kĩ thuật lập trình được sử dụng trong chương trình:
	- Module hóa chương trình phân tách các file và các hàm mục đích riêng rẽ độc lập tương đối
	
	- Trước hết ta có được cấu trúc của chương trình là thực hiện qua các struct:
		+ Lớn nhất là struct Game nhiệm vụ là quản lí toàn bộ trò chơi
		+ Tiếp đến là các struct ChessMove lưu giữ thông tin nước đi, KingAndRockMove nhằm quản lí sự di chuyển của vua và từng quân xe 1 trên bàn cờ
cùng lịch sử di chuyển của chúng để có thể Undo cho đúng, ChessPiece lưu giữ những thông tin cơ bản nhất về từng quân cờ như khả năng di chuyển,loại,giá trị của chúng
	
	- Việc render game thực hiện thông qua các hàm nền tảng nằm trong file header render.h
		+ Render 1 trạng thái bàn cờ thì lại là kết hợp hàm trong render và vector<vector<int>> board là biểu diễn bàn cờ dạng mảng 2 chiều
		
	- Sử dụng kiến thức đồ họa SDL2, vector, pair, struct,...
	
5. Kết luận, hướng phát triển và tâm đắc rút ra khi làm ra chương trình
	- Chương trình vẫn còn nhiều thiếu sót gây xảy ra bug trong 1 số trường hợp đặc biệt
	- Cách xây dựng chương trình thế này không thích hợp để làm thuật toán AI nên muốn phát triển thì phải thay đổi các biểu thị trạng thái game và hầu như toàn bộ cấu trúc
	
	- Qua việc xây dựng chương trình ta học được cách tạo ra 1 chương trình với cấu trúc logic khá phức tạp, module hóa chương trình, quản lí game và cả cách để Debug chương trình khi gặp lỗi
	