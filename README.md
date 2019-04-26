# SoalShift_Modul4_F13
## Arini Puspitasari 05111740000040
## Nur Muhammad Husnul Habib Yahya 05111740000094

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
