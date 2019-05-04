# SoalShift_Modul4_F13
## Arini Puspitasari 05111740000040
## Nur Muhammad Husnul Habib Yahya 05111740000094

## 1. File System
File system adalah struktur logika yang digunakan untuk mengendalikan akses data seperti bagaimana dia disimpan maupun diambil. File system sendiri memiliki banyak jenis dengan penggunaan algoritma yang tentu berbeda.

### 1.1 Tipe File System
#### 1. File System Disk

File system disk adalah file system yang didesain untuk menyimpan data pada sebuah media penyimpan data. Contohnya: FAT (FAT 12, FAT 16, FAT 320), NTFS, HFS, HFS+, ext2, ext3, ext4, ISO 9660, ODS-5 dan UDF.

#### 2. File System Flash

File system flash adalah file system yang didesain untuk menyimpan data pada media flash memory. Hal ini menjadi lazim ketika jumlah perangkat mobile semakin banyak dan kapasitas memory flash yang semakin besar.

#### 3. File System Database

Konsep baru untuk manajemen file adalah konsep file system berbasis database. Sebagai perbaikan bagi Manajemen terstruktur hirarkis, file diidentifikasi oleh karakteristiknya, seperti tipe file, topik, pembuat, atau metadata yang sama.

#### 4. File System Transaksional

Setiap operasi disk dapat melibatkan perubahan ke sejumlah file dan struktur disk yang berbeda. Dalam banyak kasus, perubahan ini berhubungan. Hal ini berarti bahwa operasi ini dieksekusi pada waktu yang sama.

#### 5. File System Jaringan

File system jaringan adalah file system yang bertindak sebagai klien untuk protokol akses file jarak jauh, memberikan akses ke file pada sebuah server. Contoh dari file system jaringan ini adalah klien protokol NFS, AFS, SMB, dan klien FTP dan WebDAV.

#### 6. File System untuk Tujuan Khusus

File system untuk tujuan khusus adalah file system yang tidak termasuk disk file system atau file system jaringan. Yang termasuk dalam kategori ini adalah sistem di mana file ditata secara dinamis oleh software, ditujukan untuk tujuan tertentu seperti untuk komunikasi antar proses komputer atau space file sementara. Contohnya file system procfs (/proc) yang dipakai oleh beberapa varian Unix.

#### 7. File System Journaling

File system yang mencatat perubahan ke dalam jurnal (biasanya berupa log sirkular dalam area tertentu) sebelum melakukan perubahan ke file system. File sistem seperti ini memiliki kemungkinan yang lebih kecil mengalami kerusakan saat terjadi power failure atau system crash.

### 1.2 Virtual File System
Virtual file system adalah suatu lapisan perangkat lunak dalam kernel yang menyediakan interface file system untuk program user space. Virtual file system berfungsi agar berbagai jenis file system dapat diakses oleh aplikasi komputer dengan cara yang seragam. VFS menyediakan antarmuka antara system call dengan sistem yang sesungguhnya.

### 1.3 Dentry
Dentry atau Directory Entry merupakan sebuah struktur data yang memiliki tugas sebagai penerjemah nama berkas ke inode-nya. Contoh informasi yang disimpan dalam dentry adalah name, pointer to inode, pointer to parent dentry, use count, dan lainnya. Adapula command dalam VFS dentry adalah D_compare, D_delete, D_release.

### 1.4 Superblock
Setiap file system yang di-mount akan direpresentasikan oleh sebuah VFS Superblock. Superblock digunakan untuk menyimpan informasi mengenai partisi tersebut. Superblock menyimpan informasi sebagai berikut:

- Device: Merupakan device identifier, contohnya /dev/hda1 adalah harddisk pertama yang terdapat pada sistem memiliki device identifier 0×300.
- Inode Pointer: Merupakan suatu pointer yang menunjuk ke inode pertama pada sistem berkas.
- Blocksize: Menunjukkan ukuran suatu block dari sistem berkas, contohnya 1024 bytes.
- Superblock Operation: Merupakan suatu pointer ke sekumpulan superblock routine (fungsi) dari file system, contohnya read, write, dan sebagainya.
- File System Type: Menunjukkan tipe dari file system, contoh: EXT2, FAT, NTFS.
- File System Specific: Merupakan suatu pointer ke informasi yang dibutuhkan oleh _file system.

### 1.5 Inode
Inode adalah abstraksi VFS untuk berkas. Setiap berkas, directory, dan data lainnya pada VFS direpresentasikan oleh satu dan hanya satu VFS inode. VFS inode hanya terdapat di memori kernel dan disimpan di inode chace selama masih dibutuhkan oleh sistem. Informasi yang disimpan oleh VFS Inode diantaranya:

- Device: Menunjukan device identifier dari suatu device yang menyimpan berkas ataupun directory.
- Inode Number: Merupakan nomor inode yang unik dalam file system.
- Mode: Menggambarkan apa yang direpresentasikan oleh VFS inode.
- User ID: Merupakan identifier bagi pemilik berkas.
- Time: Menunjukkan kapan pembuatan, modifikasi, dan penulisan suatu berkas.
- Blocksize: Menunjukkan ukuran dari block yang digunakan oleh berkas.
- Inode Operations: Merupakan pointer ke suatu routine yang melakukan berbagai operasi pada inode.
- Count: Menunjukkan berapa kali suatu sistem telah menggunakan suatu inode.
- Lock: Digunakan untuk mengunci VFS inode.
- File System Specific Information: Menunjukkan informasi khusus yang dibutuhkan oleh suatu inode.

## 2. File System in Userspace (FUSE)
FUSE (Filesystem in Userspace) adalah sebuah interface dimana kita dapat membuat file system sendiri pada userspace pada linux.

Keuntungan menggunakan FUSE ialah kita dapat menggunakan library apapun yang tersedia untuk membuat file system sendiri tanpa perlu mengenali secara mendalam apa yang file system sebenarnya lakukan di kernel space. Hal ini dilakukan karena modul FUSE yang dapat menjembatani antara kode file system yang berada pada userspace dengan file system yang berada pada kernel space.

## FUSE

Salah satu contoh yang menarik dari FUSE adalah GDFS (Google Drive File System), dimana GDFS ini memungkinkan kita untuk me-mount Google Drive kita ke sistem linux dan menggunakannya seperti file linux biasa.

Untuk mengimplementasikan FUSE ini, kita harus membuat sebuah program yang terhubung dengan library libfuse. Tujuan dari program yang dibuat ini adalah menspesifikkan bagaimana file system merespon read/write/stat dari sebuah request dan untuk me-(mount) file system asli (kernel space) ke file system yang baru (userspace). Jadi di saat user berurusan dengan read/write/stat request di file system (userspace), kernel akan meneruskan input output request tersebut ke program FUSE dan program tersebut akan merespon kembali ke user.

Untuk lebih jelasnya mari kita coba membuat program FUSE.

Instalasi FUSE
Pertama-tama kita harus memstikan bahwa FUSE sudah ter-install di perangkat anda
```
$ sudo apt update
$ sudo apt install libfuse*
```

Cara Kerja FUSE:
- ```fuse_main()``` (lib/helper.c) = sebagain fungsi main (userspace), program user memanggil fungsi fuse_main() kemudian fungsi fuse_mount() dipanggil.
- ```fuse_mount()``` (lib/mount.c) = menciptakan UNIX domain socket, kemudian di fork dan menciptakan child process yang menjalankan fusermount
- ```fusermount()``` (util/fusermount.c) = untuk mengecek apakah modul FUSE sudah di load. Kemudian membuka /dev/fuse dan mengirim file handle melalu UNIX domain socket kembali ke fungsi fuse_mount()
- ```fuse_new()``` (lib/fuse.c) = menciptakan struktur data yang berisi ruang yang digukanan untuk menyimpan data file system
- ```fuse_loop()``` (lib/fuse.c) = membaca file system calls dari /dev/fuse

Ini adalah beberapa fungsi yang disediakan oleh FUSE:
```
	int (*getattr) (const char *, struct stat *);
	//Get file attributes.

	int (*readlink) (const char *, char *, size_t);
	//Read the target of a symbolic link
	
	int (*mknod) (const char *, mode_t, dev_t);
	//Create a file node. 

	int (*mkdir) (const char *, mode_t);
	//Create a directory.

	int (*unlink) (const char *);
	//Remove a file

	int (*rmdir) (const char *);
	//Remove a directory

	int (*rename) (const char *, const char *);
	//Rename a file

	int (*chmod) (const char *, mode_t);
	//Change the permission bits of a file

	int (*chown) (const char *, uid_t, gid_t);
	//Change the owner and group of a file

	int (*truncate) (const char *, off_t);
	//Change the size of a file

	int (*open) (const char *, struct fuse_file_info *);
	//File open operation.

	int (*readdir) (const char *, void *, fuse_fill_dir_t, off_t, struct fuse_file_info *);
	//Read directory

	int (*read) (const char *, char *, size_t, off_t, struct fuse_file_info *);
	//Read data from an open file

	int (*write) (const char *, const char *, size_t, off_t, struct fuse_file_info *);
	//Write data to an open file
```

Membuat Program FUSE
Fuse memiliki ```struct``` yang dinamakan ```fuse_operations``` yang didefinisikan seperti dibawah ini:
```
static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.access		= xmp_access,
	.readlink	= xmp_readlink,
	.readdir	= xmp_readdir,
	.mknod		= xmp_mknod,
	.mkdir		= xmp_mkdir,
	.symlink	= xmp_symlink,
	.unlink		= xmp_unlink,
	.rmdir		= xmp_rmdir,
	.rename		= xmp_rename,
	.link		= xmp_link,
	.chmod		= xmp_chmod,
	.chown		= xmp_chown,
	.truncate	= xmp_truncate,
	.utimens	= xmp_utimens,
	.open		= xmp_open,
	.read		= xmp_read,
	.write		= xmp_write,
	.statfs		= xmp_statfs,
	.create         = xmp_create,
	.release	= xmp_release,
	.fsync		= xmp_fsync,
  	.setxattr	= xmp_setxattr,
	.getxattr	= xmp_getxattr,
	.listxattr	= xmp_listxattr,
	.removexattr	= xmp_removexattr,
#endif
};
```

Semua atribut pada ```struct``` tersebut adalah pointer yang menuju ke fungsi. Setiap fungsi tersebut disebut FUSE saat suatu kejadian yang spesifik terjadi di file system. Sebagai contoh saat user menulis di sebuah file, sebuah fungsi yang ditunjuk oleh atribut "write" di ```struct``` akan terpanggil.

Selain itu, atribut pada ```struct``` tersebut tertulis seperti fungsi yang biasa digunakan di linux. Contohnya ialah saat kita membuat directory di FUSE maka fungsi mkdir akan dipanggil.

Untuk mengimplementasikan FUSE, kita harus menggunakan ```struct``` ini dan harus mendefinisikan fungsi yang ada di dalam ```struct``` tersebut. Setelahnya, kita mengisi ```struct``` tersebut dengan pointer dari fungsi yang ingin diimplementasikan.

Kebanyakan fungsi-fungsi yang tersedia adalah opsional, kita tidak perlu mengimplementasikan semuanya. Beberapa fungsi memang harus diimplementasikan dalam file system. Fungsi-fungsi tersebut antara lain:

- Fungsi ```getattr``` yang dipanggil saat sistem mencoba untuk mendapatkan atribut dari sebuah file.
- Fungsi ```readdir``` yang dipanggil saat user mencoba untuk menampilkan file dan direktori yang berada pada suatu direktori yang spesifik.
- Fungsi ```read``` yang dipanggil saat sistem mencoba untuk membaca potongan demi potongan data dari suatu file.

Contoh program FUSE sederhanaa yang hanya menggunakan 3 fungsi tersebut.
```
#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static int xmp_getattr(const char *path, struct stat *stbuf)
{
	int res;

	res = lstat(path, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(path);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		if (filler(buf, de->d_name, &st, 0))
			break;
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
	int fd;
	int res;

	(void) fi;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
```

Setelah itu kode dapat di-compile dengan cara

```gcc -Wall `pkg-config fuse --cflags` [file.c] -o [output] `pkg-config fuse --libs` ```

Lalu buat sebuah direktori sebagai tujuan pembuatan FUSE dan menjalankan FUSE pada direktori tersebut.
```
$ mkdir [direktori tujuan]
$ ./[output] [direktori tujuan]
```

Setelah program dijalankan, masuklah kedalam direktori tujuan tersebut. Isi dari direktori tersebut adalah list folder yang sama seperti yang ada di dalam ```root``` atau``` /.```

Sesuai dengan penjelasan di awal di mana FUSE dapat memodifikasi file system di userspace tanpa perlu mengubah kode yang ada pada kernel, di sini kita coba memodifikasi kode FUSE tadi agar FUSE tersebut menampilkan apa yang ada di dalam folder ```/home/[user]/Documents```. Ubah kode FUSE tadi seperti yang ada dibawah ini:
```
#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/[user]/Documents";

static int xmp_getattr(const char *path, struct stat *stbuf)
{
  int res;
	char fpath[1000];
	sprintf(fpath,"%s%s",dirpath,path);
	res = lstat(fpath, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		res = (filler(buf, de->d_name, &st, 0));
			if(res!=0) break;
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;
  int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
```

## Soal Latihan
### Soal Latihan 1
Buat sebuah file sistem yang kamu buat ke ```/home/[user]/Downloads```, lalu ubah nama file yang ada pada folder tersebut menjadi ```[nama file].[ekstensi].bak```. File .bak tersebut hanya dapat dibaca.

jawab:
```
#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/nmhhabiby/Downloads";

static int xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;
    char fpath[1000];
    sprintf(fpath, "%s%s", dirpath, path);
    int a = strlen(fpath);
    if (fpath[a - 1] == 'k' && fpath[a - 2] == 'a' && fpath[a - 3] == 'b' && fpath[a - 4] == '.')
    {
        fpath[a - 4] = '\0';
    }
    res = lstat(fpath, stbuf);

    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info *fi)
{
    char fpath[1000];
    if (strcmp(path, "/") == 0)
    {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
    else
        sprintf(fpath, "%s%s", dirpath, path);
    int res = 0;

    DIR *dp;
    struct dirent *de;

    (void)offset;
    (void)fi;

    dp = opendir(fpath);
    if (dp == NULL)
        return -errno;

    while ((de = readdir(dp)) != NULL)
    {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
        strcat(de->d_name, ".bak");
        res = (filler(buf, de->d_name, &st, 0));
        if (res != 0)
            break;
    }

    closedir(dp);
    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
                    struct fuse_file_info *fi)
{
    char fpath[1000];
    if (strcmp(path, "/") == 0)
    {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
    else
    {
        sprintf(fpath, "%s%s", dirpath, path);
        int a = strlen(fpath);
        if (fpath[a - 1] == 'k' && fpath[a - 2] == 'a' && fpath[a - 3] == 'b' && fpath[a - 4] == '.')
        {
            fpath[a - 4] = '\0';
        }
    }
    int res = 0;
    int fd = 0;

    (void)fi;
    fd = open(fpath, O_RDONLY);
    if (fd == -1)
        return -errno;

    res = pread(fd, buf, size, offset);
    if (res == -1)
        res = -errno;

    close(fd);
    return res;
}

static struct fuse_operations xmp_oper = {
    .getattr = xmp_getattr,
    .readdir = xmp_readdir,
    .read = xmp_read,
};

int main(int argc, char *argv[])
{
    umask(0);
    return fuse_main(argc, argv, &xmp_oper, NULL);
}

// int a = strlen(fpath);
// if (fpath[a - 1] == 'k' && fpath[a - 2] == 'a' && fpath[a - 3] == 'b' && fpath[a - 4] == '.')
// {
//     fpath[a - 4] = '\0';
//     char *permission;
//     sprintf(permission, "chmod 000 %s", fpath);
//     system(permission);
// }
```

### Soal Latihan 2
Buat sebuah file system yang mengarah ke ```/home/[user]/Documents```. Pada saat membuka file dengan ekstensi .pdf, .doc, .txt pada direktori Documents akan muncul pesan error “Terjadi kesalahan! File berisi konten berbahaya.” dan tidak dapat membaca file tersebut. Setelah memunculkan pesan error, file tersebut diganti namanya menjadi ```<namafile>.<ekstensi>.ditandai```. Setelah memunculkan pesan error dan mengganti nama file tadi, file tersebut otomatis dipindahkan ke direktori rahasia. Jika folder rahasia belum ada, maka secara otomatis akan membuat direktori ```“rahasia”``` sebelum dipindahkan dan file tidak bisa di read write execute.

jawab :
```
#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/nmhhabiby/Documents";

static int xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;
    char fpath[1000];
    sprintf(fpath, "%s%s", dirpath, path);
    res = lstat(fpath, stbuf);

    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info *fi)
{
    char fpath[1000];
    if (strcmp(path, "/") == 0)
    {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
    else
        sprintf(fpath, "%s%s", dirpath, path);
    int res = 0;

    DIR *dp;
    struct dirent *de;

    (void)offset;
    (void)fi;

    dp = opendir(fpath);
    if (dp == NULL)
        return -errno;

    while ((de = readdir(dp)) != NULL)
    {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
        res = (filler(buf, de->d_name, &st, 0));
        if (res != 0)
            break;
    }

    closedir(dp);
    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
                    struct fuse_file_info *fi)
{
    char fpath[1000];
    if (strcmp(path, "/") == 0)
    {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
    else
        sprintf(fpath, "%s%s", dirpath, path);
    char simpananDir[1024];
    sprintf(simpananDir, "%s/rahasia/", dirpath);
    DIR *simpanan = opendir(simpananDir);
    if (!simpanan)
        mkdir(simpananDir, 0700);
    if (strstr(fpath, ".txt") != NULL || strstr(fpath, ".doc") != NULL || strstr(fpath, ".pdf") != NULL)
    {
        system("zenity --error --text=\"Terjadi Kesalahan! File berisi konten berbahaya.\n\" --title=\"Perhatian!\"");
        if (strstr(fpath, ".ditandai") == NULL)
        {
            char namafile[50];
            sprintf(namafile, "%s.ditandai", fpath);
            rename(fpath, namafile);
            char permission[50];
            sprintf(permission, "cd %s; chmod 000 %s", simpananDir, path);
            printf("%s", path);
            char moveC[100];
            sprintf(moveC, "mv %s %s", namafile, simpananDir);
            system(moveC);
            system(permission);
        }
    }
    int res = 0;
    int fd = 0;

    (void)fi;
    fd = open(fpath, O_RDONLY);
    if (fd == -1)
        return -errno;

    res = pread(fd, buf, size, offset);
    if (res == -1)
        res = -errno;

    close(fd);
    return res;
}

static struct fuse_operations xmp_oper = {
    .getattr = xmp_getattr,
    .readdir = xmp_readdir,
    .read = xmp_read,
};

int main(int argc, char *argv[])
{
    umask(0);
    return fuse_main(argc, argv, &xmp_oper, NULL);
}
```

### soal 1
Semua nama file dan folder harus terenkripsi.
Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher. Namun, Kusuma mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang dipakai:

```qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0```

Misalkan ada file bernama “halo” di dalam folder “INI_FOLDER”, dan key yang dipakai adalah 17, maka:
“INI_FOLDER/halo” saat belum di-mount maka akan bernama “n,nsbZ]wio/QBE#”, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi “INI_FOLDER/halo” .
Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan

Penjelasan :
1. Abaikan karakter / dengan cara :
```if (strcmp(path, "/") == 0)
    {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
```
2. Ubah karakter selain / menjadi terdeskripsi kembali seperti semula dengan cara di-mount yaitu :
``` else
    {
        strcpy(toBeSolved, path);
        ChiperSolve(0);
        sprintf(fpath, "%s%s", dirpath, solved);
        Reset();
    }
```

### soal 2
Semua file video yang tersimpan secara terpecah-pecah (splitted) harus secara otomatis tergabung (joined) dan diletakkan dalam folder “Videos”
Urutan operasi dari kebutuhan ini adalah:
a. Tepat saat sebelum file system di-mount

   i. Secara otomatis folder “Videos” terbuat di root directory file system
   
   ii.Misal ada sekumpulan file pecahan video bernama “computer.mkv.000”, “computer.mkv.001”, “computer.mkv.002”, dst. Maka secara otomatis file pecahan tersebut akan di-join menjadi file video “computer.mkv”
Untuk mempermudah kalian, dipastikan hanya video file saja yang terpecah menjadi beberapa file. File pecahan tersebut dijamin terletak di root folder fuse

   iii. Karena mungkin file video sangat banyak sehingga mungkin saja saat menggabungkan file video, file system akan membutuhkan waktu yang lama untuk sukses ter-mount. Maka pastikan saat akan menggabungkan file pecahan video, file system akan membuat 1 thread/proses(fork) baru yang dikhususkan untuk menggabungkan file video tersebut
   
   iv. Pindahkan seluruh file video yang sudah ter-join ke dalam folder “Videos”
   
   v. Jangan tampilkan file pecahan di direktori manapun
b. Tepat saat file system akan di-unmount

   i. Hapus semua file video yang berada di folder “Videos”, tapi jangan hapus file pecahan yang terdapat di root directory file system
   
   ii.Hapus folder “Videos” 

Penjelasan :

### soal 3
Sebelum diterapkannya file system ini, Atta pernah diserang oleh hacker LAPTOP_RUSAK yang menanamkan user bernama “chipset” dan “ic_controller” serta group “rusak” yang tidak bisa dihapus. Karena paranoid, Atta menerapkan aturan pada file system ini untuk menghapus “file bahaya” yang memiliki spesifikasi:
   - Owner Name 	: ‘chipset’ atau ‘ic_controller’
   - Group Name	: ‘rusak’
   - Tidak dapat dibaca
Jika ditemukan file dengan spesifikasi tersebut ketika membuka direktori, Atta akan menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses dalam file “filemiris.txt” (format waktu bebas, namun harus memiliki jam menit detik dan tanggal) lalu menghapus “file bahaya” tersebut untuk mencegah serangan lanjutan dari LAPTOP_RUSAK.

Penjelasan :
1. Abaikan karakter / dengan cara :
```if (strcmp(path, "/") == 0)
    {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
```
2. Ubah karakter selain / menjadi terdeskripsi kembali seperti semula dengan cara di-mount yaitu :
``` else
    {
        strcpy(toBeSolved, path);
        ChiperSolve(0);
        sprintf(fpath, "%s%s", dirpath, solved);
        Reset();
    }
```
3. Menghapus "file bahaya" ketika memiliki spesifikasi dengan owner name 'chipset' atau 'ic_controller'
```        if ((strcmp(pw->pw_name, "chipset") == 0 || strcmp(pw->pw_name, "ic_controller") == 0) && strcmp(gr->gr_name, "rusak") == 0)
        {
            FILE *cek, *file;
            cek = fopen(name, "r");
            if (cek == NULL)
            {
                char miris[1000];
                strcpy(toBeSolved, "filemiris.txt");
                ChiperSolve(0);
                sprintf(miris, "%s%s", dirpath, solved);
                Reset();
                file = fopen(miris, "a");

                struct tm *lastA;
                lastA = (gmtime(&fstat.st_atime));

                char isiFile[1000];
                sprintf(isiFile, "%s %d:%d %d:%d:%d %d/%d/%d\n", de->d_name, pw->pw_uid, gr->gr_gid, lastA->tm_hour, lastA->tm_min, lastA->tm_sec, lastA->tm_mday, lastA->tm_mon + 1, lastA->tm_year + 1900);
                fputs(isiFile, file);

                fclose(file);

                check = 1;
                remove(name);
            }
```
4. Menghapus "file berbehaya" ketika memiliki spesifikasi dengan group name 'rusak'
```if (check == 0)
        {
            int flag = 0;
            if (strlen(de->d_name) < 3)
            {
                int i;
                for (i = 0; i < strlen(de->d_name); i++)
                {
                    if (de->d_name[i] == '.')
                        flag++;
                }
            }
            if (flag == 0)
            {
                strcpy(toBeSolved, de->d_name);
                ChiperSolve(1);
                strcpy(de->d_name, solved);
                Reset();
            }
            res = (filler(buf, de->d_name, &st, 0));
            if (res != 0)
                break;
        }
    }
 ```
 
### soal 4
Pada folder YOUTUBER, setiap membuat folder permission foldernya akan otomatis menjadi 750. Juga ketika membuat file permissionnya akan otomatis menjadi 640 dan ekstensi filenya akan bertambah “.iz1”. File berekstensi “.iz1” tidak bisa diubah permissionnya dan memunculkan error bertuliskan “File ekstensi iz1 tidak boleh diubah permissionnya.”

Penjelasan :
1. Abaikan karakter / dengan cara :
```if (strcmp(path, "/") == 0)
    {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
```
2. Ubah karakter selain / menjadi terdeskripsi kembali seperti semula dengan cara di-mount yaitu :
``` else
    {
        strcpy(toBeSolved, path);
        ChiperSolve(0);
        sprintf(fpath, "%s%s", dirpath, solved);
        Reset();
    }
```
3. Membuat folder permission
```else
    {
        strcpy(toBeSolved, path);
        ChiperSolve(0);
        sprintf(fpath, "%s%s", dirpath, solved);
        Reset();
        if (strstr(path, "/YOUTUBER/") != NULL)
        {
            strcpy(check, strstr(path, "/YOUTUBER/"));
            strcpy(check, &check[strlen("/YOUTUBER/")]);
            if (strstr(check, "/") == NULL)
                flag = 1;
        }
    }
```
4. Menghasilkan 750 apabila berhasil membuat folder permission
```
if (flag == 1)
    {
        printf("=====bikin dir di utuber=====\n");
        mode = 0750;
    }
```
5. Membuat file permission
```
if (strstr(path, "/YOUTUBER/") != NULL)
    {
        strcpy(check, strstr(path, "/YOUTUBER/"));
        strcpy(check, &check[strlen("/YOUTUBER/")]);
        if (strstr(check, "/") == NULL && strstr(check, ".swp") == NULL)
            flag = 1;
    }
```
6. Menghasilkan 640 apabila berhasil membuat file permission
```
if (flag == 1)
        mode = 0640;
````
7. Menambah file permissionnya dengan ".iz1"
```
if (flag == 1)
    {
        printf("======bikin file di utuber=====\n");
        char newName[1000];
        strcpy(toBeSolved, ".iz1");
        ChiperSolve(0);
        sprintf(newName, "%s%s", fpath, solved);
        Reset();
```
8. Menambah folder permissionnya dengan ".iz1"
```
if (strstr(path, ".iz1") != NULL)
        flag = 1;

    if (flag == 1)
    {
        char warning[1000];
        strcpy(warning, "zenity --error --text=\"File ekstensi iz1 tidak boleh dirubah permissionnya.\n\" --title=\"Perhatian!\"");
        system(warning);
        return -1;
    }
```
### soal 5
Ketika mengedit suatu file dan melakukan save, maka akan terbuat folder baru bernama Backup kemudian hasil dari save tersebut akan disimpan pada backup dengan nama namafile_[timestamp].ekstensi. Dan ketika file asli dihapus, maka akan dibuat folder bernama RecycleBin, kemudian file yang dihapus beserta semua backup dari file yang dihapus tersebut (jika ada) di zip dengan nama namafile_deleted_[timestamp].zip dan ditaruh ke dalam folder RecycleBin (file asli dan backup terhapus). Dengan format [timestamp] adalah yyyy-MM-dd_HH:mm:ss
