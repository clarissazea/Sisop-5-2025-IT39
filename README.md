# Sisop-5-2025-IT39

## Kelompok

Nama | NRP
--- | ---
Ahmad Wildan Fawwaz | 5027241001
Clarissa Aydin Rahmazea | 5027241014
Muhammad Rafi' Adly | 5027241082

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

7. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb


## Laporan

Kami mengubah/melengkapi file-file berikut.
* [kernel.c](src/kernel.c)
* [std_lib.c](src/std_lib.c)
* [std_lib.h](include/std_lib.h) (hanya mengubah tipe variabel)
* [shell.c](src/shell.c) (hardcode disini)
* [shell.h](include/shell.h) (menyesuaikan dengan fungsi yang ada di `shell.c`)
* [makefile](./makefile)

Pertama-tama kami melengkapi fungsi yang ada di `kernel.c` sebagai file utama untuk menjalankan OS.
```c
int textColor = 0x07; //default (putih)

int main() {
  clearScreen(textColor);
  shell();
}

void printString(char *str) {
  while (*str != '\0') {
    interrupt(0x10, 0x0E00 + *str, 0, 0, 0);
    str++;
  }
}
```
Mendeklarasikan textColor untuk warna text yang akan digunakan di fungsi `clearScreen`. Di fungsi utama `int main()` membersihkan layar lalu memanggil fungsi `shell()` yang ada di file [shell.c](src/shell.c).  
Fungsi `printString` untuk memunculkan output di layar, menggunakan while loop dan `interrupt` yang sebelumnya dideklarasikan di file [kernel.asm](src/kernel.asm).  
Kemudian fungsi `readString` untuk membaca input dari user
```c
void readString(char *buf) {
  int i = 0;
  char c;
  while (1) {
    c = interrupt(0x16, 0x0000, 0, 0, 0) & 0xFF;
    if (c == 13) {
      buf[i] = '\0';
      printString("\r\n");
      break;
    } else if (c == 8) {
      if (i > 0) {
        i--;
        printString("\b \b");
      }
    } else {
      buf[i++] = c;
      interrupt(0x10, 0x0E00 + c, 0, 0, 0);
    }
  }
}
```
variabel `buf` adalah input dari user. Variabel `c` digunakan untuk menyimpan dan membaca input menggunakan `interrupt` yang berupa ASCII. Jika user menekan `ENTER` (ASCII = 13), maka kursor akan bergerak ke bawah dan keluar dari looping. Jika user menekan `BACKSPACE` (ASCII = 8), maka kursor akan bergerak ke kiri dan menghapus input user sebelumnya.  
Fungsi `clearScreen` dijelaskan di [Soal 4](###Soal-4)

### Soal 1
Nomor 1 adalah mengulang apa yang user input-kan. Ini ada di dalam fungsi `shell` di file [shell.c](src/shell.c).
```c
void shell() {
    // ...
    while (1) {
        // ...

        readString(buf);
        parseCommand(buf, cmd, args);

	// ...

	else {
            printString(buf);
            printString("\r\n");
        }
    }
}
```
Dalam while loop, fungsi `readString` membaca input dari user. Jika input user tidak memenuhi kondisi tertentu (soal lain), maka memunculkan output berupa apa yang user input-kan.
#### Dokumentasi
<img width="960" alt="image" src="https://github.com/user-attachments/assets/a3c3eb19-0612-4c43-8118-58c3a0f8e0c9" />

### Soal 2
Nomor 2 adalah memunculkan output `gurt` saat user meng-input-kan `yo`, dan sebaliknya. Ini ada di dalam fungsi `shell` di file [shell.c](src/shell.c).
```c
void shell() {
    // ...
    while (1) {
        // ...

        readString(buf);
        parseCommand(buf, cmd, args);

	if (strcmp(cmd, "yo")) {
            printString("gurt\r\n");
        } else if (strcmp(cmd, "gurt")) {
            printString("yo\r\n");
    	}

	// ...
}
```
#### Dokumentasi
<img width="960" alt="image" src="https://github.com/user-attachments/assets/7cde0a10-4334-4e19-a11c-909347389a15" />

### Soal 3
Dikerjakan oleh Clarissa Aydin Rahmazea (5027241014)

Shell harus mendukung perintah untuk mengubah username prompt.

Perintah:

- `user <username>` → untuk mengganti username menjadi `<username>`.
- `user` → mengembalikan username ke default `(user)`.

Prompt shell akan menampilkan `<username> >` setiap kali menerima input berikutnya.

```
else if (strcmp(cmd, "user")) {
    if (args[0][0] != '\0') {
        strcpy(username, args[0]);
        printString("Username changed to ");
        printString(username);
        printString("\r\n");
    } else {
        strcpy(username, "user");
        printString("Username changed to user\r\n");
    }
}
```

Penjelasan code:
- Command `"user"` diperiksa menggunakan `strcmp(cmd, "user").`
- Argumen pertama `(args[0])` dicek apakah kosong `('\0').` Jika tidak kosong, maka `username` di-update dengan nilai dari `args[0]` menggunakan `strcpy()`.
- Jika kosong, username di-reset ke default `"user"`.
- Setelah username diubah, shell menampilkan notifikasi: `"Username changed to <username>"` atau `"Username changed to user"`.

Penjelasan alur:
1. Pengguna memasukkan perintah user diikuti nama.
2. Shell membaca argumen pertama (jika ada).
3. Jika ada nama baru, shell mengupdate variabel username.
4. Jika tidak ada nama baru, shell mengembalikan username ke default.
5. Username baru akan tampil di prompt pada iterasi berikutnya:

#### Dokumentasi

### Soal 4
Dikerjakan oleh Ahmad Wildan Fawwaz (5027241001)

Inti soal:    
- `grandcompany maelstrom`: clear screen + teks jadi merah + prompt jadi user@Storm
- `grandcompany twinadder`: clear screen + teks jadi kuning + prompt jadi user@Serpent
- `grandcompany immortalflames`: clear screen + teks jadi biru + prompt jadi user@Flame
- `grandcompany <selain atau kosong>`: tampilkan pesan error.  

Implementasi Kode: 
Edit pada file Shell.c
Pada bagian setelah if else berikut 
```c
if (strcmp(cmd, "yo")) {...}
```
Tepatnya setelah di bagian
```c
printString("Username changed to user\r\n");  
        }  
    }
```

Tambahkan kode berikut:
```c
} else if (strcmp(cmd, "grandcompany")) {  
        if (strcmp(args[0], "maelstrom")) {  
            textColor = 0x0C; // merah terang  
            clearScreen(textColor);  
            currentGC = STORM;  
        } else if (strcmp(args[0], "twinadder")) {  
            textColor = 0x0E; // kuning  
            clearScreen(textColor);  
            currentGC = SERPENT;  
        } else if (strcmp(args[0], "immortalflames")) {  
            textColor = 0x09; // biru  
            clearScreen(textColor);  
            currentGC = FLAME;  
        } else {  
            printString("Error: Unknown Grand Company\r\n");  
        }  
    } else if (strcmp(cmd, "clear")) {  
        textColor = 0x07;  
        clearScreen(textColor);  
        currentGC = NONE;  
        printString("Para Grand Company sedih, kamu netral.\r\n");  
    }
```
Penjelasan:   
Kode tersebut untuk memeriksa argumen `grandcompany`.   
Set warna sesuai perintah: `0x0C` (merah), `0x0E` (kuning), `0x09` (biru).   
Fungsi `clearScreen(textColor)` dipanggil untuk membersihkan terminal dengan warna baru.   
Variabel `currentGC` diatur untuk mengubah user pada prompt.   

Inti soal:   
Setelah masuk Grand Company, nama pengguna berubah menjadi user@Storm, user@Serpent, atau user@Flame.   
Tambahkan implementasi `printString(username)` ke kode shell.c pada bagian berikut:   
shell.c
```c
printString("Welcome to EorzeOS!\n");  
while (1) {...
}
```
Implementasi kodenya:
```c
printString(username);  
    if (currentGC == STORM) printString("@Storm");  
    else if (currentGC == SERPENT) printString("@Serpent");  
    else if (currentGC == FLAME) printString("@Flame");  
    printString("> ");
```
Penjelasan:   
Nama pengguna ditampilkan bersama GC yang aktif sesuai enum `currentGC`.   
Diubah ketika grandcompany dijalankan.   
`user@Storm>`, `user@Serpent>`, dan `user@Flame>` ditampilkan sebagai prompt.   

Inti soal:   
`clear`: membersihkan terminal dan mengembalikan warna ke default (putih).   
Prompt pengguna kembali menjadi `user>`, tanpa Grand Company.   

Implementasi kodenya:   
```c
} else if (strcmp(cmd, "clear")) {
    textColor = 0x07;
    clearScreen(textColor);
    currentGC = NONE;
    printString("Para Grand Company sedih, kamu netral.\r\n");
}
```
Penjelasan:   
`textColor` dikembalikan ke default `0x07` (putih).   
`currentGC` di-set ke NONE → tidak menampilkan @Storm dsb.   
Menampilkan pesan "Para Grand Company sedih, kamu netral."   

Fungsi `clearScreen(int textColor)`   
Implementasi kodenya:   
kernel.c   
```c
void clearScreen(textColor) {
  int i;
  int screenSize = 80 * 25;
  for (i = 0; i < screenSize; i++) {
    putInMemory(0xB800, i * 2, ' ');
    putInMemory(0xB800, i * 2 + 1, textColor);
  }
  interrupt(0x10, 0x0200, 0, 0, 0);
}
```
Penjelasan:   
Mengosongkan semua karakter layar (' ') dan mewarnainya dengan atribut `textColor`.   
Memastikan seluruh layar dibersihkan dan diberi warna sesuai Grand Company.   
`putInMemory` langsung mengakses memori video.   

#### Dokumentasi
![Image](https://github.com/user-attachments/assets/5876ca39-b890-4410-a618-1300ddd59ed8)
![Image](https://github.com/user-attachments/assets/fc206c9d-00ad-437d-803b-2b3a215143b7)
![Image](https://github.com/user-attachments/assets/b5f48ac3-8cd2-4aaf-9c05-45630dd33aa0)
![Image](https://github.com/user-attachments/assets/981b577f-afd1-4bd8-8cb4-e6a21f292cd8)
![Image](https://github.com/user-attachments/assets/255c42d9-cade-4cbd-a011-16be490453a5)
![Image](https://github.com/user-attachments/assets/c887bad8-db3f-4ff4-b3c7-ed5a63a5cf1b)
![Image](https://github.com/user-attachments/assets/4a592d5a-6009-49af-b7f0-ca464e268a0f)
![Image](https://github.com/user-attachments/assets/c411e89b-e987-4cf4-ba4b-1e62594a557e)


### Soal 5
Dikerjakan oleh Clarissa Aydin Rahmazea (5027241014)

### Soal 6
Dikerjakan oleh Clarissa Aydin Rahmazea (5027241014)

### Soal 7
Untuk nomor 7 yaitu membuat makefile
```
prepare:
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2880
bootloader:
	nasm -f bin src/bootloader.asm -o bin/bootloader.bin
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc
stdlib:
	bcc -ansi -Iinclude -c src/std_lib.c -o bin/std_lib.o
shell:
	bcc -ansi -Iinclude -c src/shell.c -o bin/shell.o
kernel:
	nasm -f as86 src/kernel.asm -o bin/kernel-asm.o
	bcc -ansi -Iinclude -c src/kernel.c -o bin/kernel.o
link:
	ld86 -o bin/kernel.bin -d bin/kernel.o bin/kernel-asm.o bin/std_lib.o bin/shell.o
	dd if=bin/kernel.bin of=bin/floppy.img bs=512 seek=1 count=15 conv=notrunc
build: prepare bootloader stdlib shell kernel link
clean:
	rm -f bin/*
run: clean build
```
makefile ini berfungsi untuk meng-compile file C dan Assembly menggunakan nasm untuk assembly, dan bcc untuk file C. Untuk pengisiannya kami samakan dengan langkah-langkah pembuatan OS yang ada di modul. Kemudian kami menambahkan fitur clean dan run.  
`clean` berfungsi untuk menghapus semua file yang ada di directory bin/  
`run` berfungsi untuk menjalankan perintah clean dan build, yaitu menghapus semua file output dan meng-compile-nya kembali beserta dengan floppy.img
