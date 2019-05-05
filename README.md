Soal Shift Modul 4 C11


Isnaini Nurul KurniaSari    05111740000010


Argo Galih Pribadi          05111740000150


Soal Shift Modul 4

Suatu ketika King of YouTube ASEAN, Atta Halilintar, mengunjungi laboratorium AJK karena urusan yang benar-benar genting. Prestasi dan ketenarannya ternyata menarik perhatian hacker yang ingin mencuri video-video berkualitas milik Atta, bahkan ingin mencuri password akun YouTube miliknya. Menurut intel Atta, pemimpin hacker yang berusaha menyerangnya adalah:
Hacker tersebut menyusup ke dalam file system yang ada di dalam PC Atta dengan mudah karena ternyata file system tersebut sama sekali tidak memiliki sistem pengamanan. Maka dari itu maksud Atta ke laboratorium AJK karena dia ingin kalian untuk mengembangkan file system yang aman.
Atta menginginkan nama file system yang akan kalian buat adalah “AFSHiaAP”, yang nama kepanjangannya adalah AHHA’s File System: Hierarchical and Advanced Protection. Berikut ini kebutuhan yang harus kalian penuhi:

*Soal Latihan*
1. Semua nama file dan folder harus terenkripsi
Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher. Namun, Kusuma mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang dipakai:

qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0`
Misalkan ada file bernama “halo” di dalam folder “INI_FOLDER”, dan key yang dipakai adalah 17, maka:
“INI_FOLDER/halo” saat belum di-mount maka akan bernama “n,nsbZ]wio/QBE#”, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi “INI_FOLDER/halo” .
Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan

Jawab :

Langkah pertama adalah membuat sebuah file sistem yang dibuat ke /home/isnaini/Shift4, lalu ubah nama file yang ada pada folder tersebut menjadi [nama file].[ekstensi].bak. File .bak tersebut hanya dapat dibaca.

Source Code dan penjelasan:
```
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/wait.h>
#include "chiper.h"

//NOMER 1//
static const char *dirpath = "/home/isnaini/shift4";
static int xmp_getattr(const char *path, struct stat *stbuf) //untuk mendapatkan file atribut
{
    int res;
    char fpath[1000];
    if (strcmp(path, "/") == 0) //untuk abaikan /
    {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
    else
    {
        strcpy(toBeSolved, path);//isna
        ChiperSolve(0);//isna=nxsj
        sprintf(fpath, "%s%s", dirpath, solved);//home/isna/shift4 +hasil dekrip
        Reset();
    }

    res = lstat(fpath, stbuf);

    if (res == -1)
        return -errno;

    return res;
}

//NOMER 1 Lanjutan//
static int xmp_statfs(const char *path, struct statvfs *stbuf)
{
    int res;

    char fpath[1000];
    if (strcmp(path, "/") == 0) //ketika ada chacaracter "/" maka diabaikan /
    {
        path = dirpath; //path diisi /home/isnaini/
        sprintf(fpath, "%s", path);
    }
    else
    {
        strcpy(toBeSolved, path); //toBeSolved = /blablabla
        ChiperSolve(0); // enkripsi /home/isnaini/ dienkrip
        sprintf(fpath, "%s%s", dirpath, solved); //  fpath = /home/isnaini/blablaenkrip
        Reset();
    }

    res = statvfs(fpath, stbuf);
    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
                    struct fuse_file_info *fi) //Read data from an open file
{
    char fpath[1000];
    if (strcmp(path, "/") == 0)
    {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
    else
    {
        strcpy(toBeSolved, path);
        ChiperSolve(0);
        sprintf(fpath, "%s%s", dirpath, solved);
        Reset();
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
    .mkdir = xmp_mkdir,
    .truncate = xmp_truncate,
    .utimens = xmp_utimens,
    .statfs = xmp_statfs,
    .create = xmp_create,
    .rmdir = xmp_rmdir,
    .unlink = xmp_unlink,
    .chmod = xmp_chmod,
    .write = xmp_write,
    .open = xmp_open,
    .chown = xmp_chown,
};

int main(int argc, char *argv[])
{
    umask(0);
    return fuse_main(argc, argv, &xmp_oper, NULL);
}
```
* Mengabaikan karakter "/" sesuai dengan soal; menggunakan:
```
{
   path = dirpath;
   sprintf(fpath, "%s", path);
}
```

* mengubah karakter selain karakter "/" dan menjadi terdeskripsi kembali seperti semula dengan cara di-mount yaitu 
```
{
   strcpy(toBeSolved, path);
   ChiperSolve(0);
   sprintf(fpath, "%s%s", dirpath, solved);
   Reset();
}

```


2. Semua file video yang tersimpan secara terpecah-pecah (splitted) harus secara otomatis tergabung (joined) dan diletakkan dalam folder “Videos”
Urutan operasi dari kebutuhan ini adalah:
Tepat saat sebelum file system di-mount
Secara otomatis folder “Videos” terbuat di root directory file system
Misal ada sekumpulan file pecahan video bernama “computer.mkv.000”, “computer.mkv.001”, “computer.mkv.002”, dst. Maka secara otomatis file pecahan tersebut akan di-join menjadi file video “computer.mkv”
Untuk mempermudah kalian, dipastikan hanya video file saja yang terpecah menjadi beberapa file. File pecahan tersebut dijamin terletak di root folder fuse
Karena mungkin file video sangat banyak sehingga mungkin saja saat menggabungkan file video, file system akan membutuhkan waktu yang lama untuk sukses ter-mount. Maka pastikan saat akan menggabungkan file pecahan video, file system akan membuat 1 thread/proses(fork) baru yang dikhususkan untuk menggabungkan file video tersebut
Pindahkan seluruh file video yang sudah ter-join ke dalam folder “Videos”
Jangan tampilkan file pecahan di direktori manapun
Tepat saat file system akan di-unmount
Hapus semua file video yang berada di folder “Videos”, tapi jangan hapus file pecahan yang terdapat di root directory file system
Hapus folder “Videos”.

3. Sebelum diterapkannya file system ini, Atta pernah diserang oleh hacker LAPTOP_RUSAK yang menanamkan user bernama “chipset” dan “ic_controller” serta group “rusak” yang tidak bisa dihapus. Karena paranoid, Atta menerapkan aturan pada file system ini untuk menghapus “file bahaya” yang memiliki spesifikasi:
Owner Name 	: ‘chipset’ atau ‘ic_controller’
Group Name	: ‘rusak’
Tidak dapat dibaca
Jika ditemukan file dengan spesifikasi tersebut ketika membuka direktori, Atta akan menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses dalam file “filemiris.txt” (format waktu bebas, namun harus memiliki jam menit detik dan tanggal) lalu menghapus “file bahaya” tersebut untuk mencegah serangan lanjutan dari LAPTOP_RUSAK.

Jawab :

* Fungsi untuk read_dir:
```
static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info *fi)
{
    char fpath[1000];
    if (strcmp(path, "/") == 0) // jika /
    {
        path = dirpath; //path = /home/isnaini/
        sprintf(fpath, "%s", path); //isi fpath dengan /home/isnaini/
    }
    else // jika tidak /
    {
        strcpy(toBeSolved, path); //
        ChiperSolve(0); //enkripsi
        sprintf(fpath, "%s%s", dirpath, solved);
        Reset();
    }

    int res = 0;
    DIR *dp;
    struct dirent *de;
    (void)offset;
    (void)fi;
    dp = opendir(fpath); //buka direktori fpath
    if (dp == NULL)
        return -errno;

    while ((de = readdir(dp)) != NULL) //menlooping untuk membuka isi folder
    {
        char name[1000];
        sprintf(name, "%s/%s", fpath, de->d_name); //isi name dengan /home/isnaini/ + nama folder/file
        struct stat st;
        struct stat fstat;
        memset(&st, 0, sizeof(st));

        stat(name, &fstat);

        st.st_ino = de->d_ino; 
        st.st_mode = de->d_type << 12; 

        struct passwd *pw = getpwuid(fstat.st_uid);//dapatkan uid owner
        struct group *gr = getgrgid(fstat.st_gid); //dapatkan gid grub owner

        int check = 0;
 
 
        if ((strcmp(pw->pw_name, "chipset") == 0 || strcmp(pw->pw_name, "ic_controller") == 0) && strcmp(gr->gr_name, "rusak") == 0)
        {//jika owner name chipset atau ic_controller dan groupname rusak
            FILE *cek, *file;
            cek = fopen(name, "r");
            if (cek == NULL)
            {
                char miris[1000];
                strcpy(toBeSolved, "filemiris.txt");
                ChiperSolve(0);//enkripsi filemiris.txt
                sprintf(miris, "%s%s", dirpath, solved);
                Reset();
                file = fopen(miris, "a");

                struct tm *lastA;
                lastA = (gmtime(&fstat.st_atime)); //dapatkan waktu

                char isiFile[1000]; 
                sprintf(isiFile, "%s %d:%d %d:%d:%d %d/%d/%d\n", de->d_name, pw->pw_uid, gr->gr_gid, lastA->tm_hour, lastA->tm_min, lastA->tm_sec, lastA->tm_mday, lastA->tm_mon + 1, lastA->tm_year + 1900);
               //format nama file:direktori,pwuid,grub,jam,menit,sekon
                fputs(isiFile, file);

                fclose(file);

                check = 1; //check dibuat 1
                remove(name);//hapus
            }
            else
                fclose(cek);
        }
        if (check == 0)
        {
            int flag = 0;
            if (strlen(de->d_name) < 3) //jika panjang nama file < 3
            {
                int i;
                for (i = 0; i < strlen(de->d_name); i++) //
                {
                    if (de->d_name[i] == '.') //jika ada titiknya
                        flag++;
                }
            }
            if (flag == 0)
            {
                strcpy(toBeSolved, de->d_name); //
                ChiperSolve(1); //dekripsi
                strcpy(de->d_name, solved);
                Reset();
            }
            res = (filler(buf, de->d_name, &st, 0));
            if (res != 0)
                break;
        }
    }

    closedir(dp);
    return 0;
}

```

* Mengabaikan character "/" dengan cara ;
```
  {
     path = dirpath;
     sprintf(fpath, "%s", path);
  }

```

* Mengubah selain karakter "/" menjadi terdeskripsi kembali seperti semula dengan cara di-mount yaitu :
```
  {
        strcpy(toBeSolved, path);
        ChiperSolve(0);
        sprintf(fpath, "%s%s", dirpath, solved);
        Reset();
   }
```

* Menghapus "file bahaya" ketika memiliki spesifikasi dengan owner name 'chipset' atau 'ic_controller'

```
if (cek == NULL)
 {
  char miris[1000];
  strcpy(toBeSolved, "filemiris.txt");
  ChiperSolve(0);//enkripsi filemiris.txt
  sprintf(miris, "%s%s", dirpath, solved);
  Reset();
  file = fopen(miris, "a");
  struct tm *lastA;
  lastA = (gmtime(&fstat.st_atime)); //dapatkan waktu
  char isiFile[1000]; 
  sprintf(isiFile, "%s %d:%d %d:%d:%d %d/%d/%d\n", de->d_name, pw->pw_uid, gr->gr_gid, lastA->tm_hour, lastA->tm_min, lastA->tm_sec,  lastA->tm_mday, lastA->tm_mon + 1, lastA->tm_year + 1900); //format nama file:direktori,pwuid,grub,jam,menit,sekon
 fputs(isiFile, file);
 fclose(file);
 check = 1; //check dibuat 1
 remove(name);//hapus
 }
```
* Menghapus "file berbehaya" ketika memiliki spesifikasi dengan group name 'rusak'

```
if (check == 0)
        {
            int flag = 0;
            if (strlen(de->d_name) < 3) //jika panjang nama file < 3
            {
                int i;
                for (i = 0; i < strlen(de->d_name); i++) //
                {
                    if (de->d_name[i] == '.') //jika ada titiknya
                        flag++;
                }
            }
            if (flag == 0)
            {
                strcpy(toBeSolved, de->d_name); //
                ChiperSolve(1); //dekripsi
                strcpy(de->d_name, solved);
                Reset();
            }
            res = (filler(buf, de->d_name, &st, 0));
            if (res != 0)
                break;
        }
```


4. Pada folder YOUTUBER, setiap membuat folder permission foldernya akan otomatis menjadi 750. Juga ketika membuat file permissionnya akan otomatis menjadi 640 dan ekstensi filenya akan bertambah “.iz1”. File berekstensi “.iz1” tidak bisa diubah permissionnya dan memunculkan error bertuliskan “File ekstensi iz1 tidak boleh diubah permissionnya.”

Source code dan Penjelasan:
* untuk mengubah karakter "/" menjadi terdekrip adalah :
```
{
        strcpy(toBeSolved, path);
        ChiperSolve(0);
        sprintf(fpath, "%s%s", dirpath, solved);
        Reset();
}

```

* mengabaikan selain karakter "/" adalah :
```
{
        path = dirpath;
        sprintf(fpath, "%s", path);
}
```

* untuk fungsi folder permission:
```
static int xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{ //ketika membuat file
    (void)fi;
    char check[1000];
    int flag = 0;
    if (strstr(path, "/YOUTUBER/") != NULL) //jika ada string youtuber di path
    {
        strcpy(check, strstr(path, "/YOUTUBER/")); 
        strcpy(check, &check[strlen("/YOUTUBER/")]);
        if (strstr(check, "/") == NULL && strstr(check, ".swp") == NULL) //jika tidak ditemukan 
            flag = 1;
    }

    char fpath[1000];
    if (strcmp(path, "/") == 0) //abaikan character "/" /
    {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
    else //jika ada namanya
    {
        strcpy(toBeSolved, path);
        ChiperSolve(0); //enkripsi path
        sprintf(fpath, "%s%s", dirpath, solved); //masukan ke dir path
        Reset();
    }

    if (flag == 1)
        mode = 0640; //permision menjadi 0640

    int res;
    res = creat(fpath, mode);//buat file dengan permision 640

    if (flag == 1)
    {
        printf("======bikin file di utuber=====\n");
        char newName[1000];
        strcpy(toBeSolved, ".iz1"); 
        ChiperSolve(0);//endkripsi .iz1
        sprintf(newName, "%s%s", fpath, solved); 
        printf("++++++++++++++++fpath = %s",fpath);
        Reset();
        int child = fork();
        if (child == 0)
        {
            char *mv_argv[] = {"mv", fpath, newName, NULL};
            execvp("mv", mv_argv);
        }
    }

    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_mkdir(const char *path, mode_t mode) //Create a directory. 
{
    int res;
    char check[1000];
    int flag = 0;

    char fpath[1000];
    if (strcmp(path, "/") == 0)
    {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
    else
    {
        strcpy(toBeSolved, path);
        ChiperSolve(0);
        sprintf(fpath, "%s%s", dirpath, solved);
        Reset();
        if (strstr(path, "/YOUTUBER/") != NULL) //jika ada youtuber dalam path
        {
            strcpy(check, strstr(path, "/YOUTUBER/")); //
            strcpy(check, &check[strlen("/YOUTUBER/")]);//
            if (strstr(check, "/") == NULL) //jika mengandung '/'
                flag = 1;
        }
    }

    if (flag == 1)
    {
        printf("=====bikin dir di youtuber=====\n");
        mode = 0750; //permision jadi 0750
    }

    res = mkdir(fpath, mode); //buat direktori dengan permision 0750
    if (res == -1)
        return -errno;

    return 0;
}
```

5. Ketika mengedit suatu file dan melakukan save, maka akan terbuat folder baru bernama Backup kemudian hasil dari save tersebut akan disimpan pada backup dengan nama namafile_[timestamp].ekstensi. Dan ketika file asli dihapus, maka akan dibuat folder bernama RecycleBin, kemudian file yang dihapus beserta semua backup dari file yang dihapus tersebut (jika ada) di zip dengan nama namafile_deleted_[timestamp].zip dan ditaruh ke dalam folder RecycleBin (file asli dan backup terhapus). Dengan format [timestamp] adalah yyyy-MM-dd_HH:mm:ss

Catatan: 
Semua nama file dan folder yang terdapat pada soal harus memenuhi syarat soal no. 1 (terenkripsi saat belum di-mount dan terdekripsi saat di-mount)
Tidak diperkenankan menggunakan system() dan exec*(), kecuali ada pengecualian di butir soal.
Untuk soal nomor 3 diharapkan secara manual membuat user dan group-nya. Pengecekan file dilakukan setiap membuka direktori.
Untuk soal nomor 4 dan 5 diperbolehkan menggunakan exec*().
Pengerjaan hanya dilakukan dalam 1 file program C dengan format nama AFSHiaAP_[Kelompok].c . 
File System AFSHiaAP mengarah ke folder /home/[user]/shift4.


