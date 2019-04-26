#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/wait.h>
#include "chiper.h"

static const char *dirpath = "/home/nmhhabiby/shift4/";

static int xmp_statfs(const char *path, struct statvfs *stbuf)
{
    int res;

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

    res = statvfs(fpath, stbuf);
    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{

    (void)fi;

    char check[1000];
    int flag = 0;
    if (strstr(path, "/YOUTUBER/") != NULL)
    {
        strcpy(check, strstr(path, "/YOUTUBER/"));
        strcpy(check, &check[strlen("/YOUTUBER/")]);
        if (strstr(check, "/") == NULL && strstr(check, ".swp") == NULL)
            flag = 1;
    }

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

    if (flag == 1)
        mode = 0640;

    int res;
    res = creat(fpath, mode);

    if (flag == 1)
    {
        printf("======bikin file di utuber=====\n");
        char newName[1000];
        strcpy(toBeSolved, ".iz1");
        ChiperSolve(0);
        sprintf(newName, "%s%s", fpath, solved);
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

static int xmp_mkdir(const char *path, mode_t mode)
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
        if (strstr(path, "/YOUTUBER/") != NULL)
        {
            strcpy(check, strstr(path, "/YOUTUBER/"));
            strcpy(check, &check[strlen("/YOUTUBER/")]);
            if (strstr(check, "/") == NULL)
                flag = 1;
        }
    }

    if (flag == 1)
    {
        printf("=====bikin dir di utuber=====\n");
        mode = 0750;
    }

    res = mkdir(fpath, mode);
    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_truncate(const char *path, off_t size)
{
    int res;

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

    res = truncate(fpath, size);
    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_utimens(const char *path, const struct timespec ts[2])
{
    int res;
    struct timeval tv[2];

    tv[0].tv_sec = ts[0].tv_sec;
    tv[0].tv_usec = ts[0].tv_nsec / 1000;
    tv[1].tv_sec = ts[1].tv_sec;
    tv[1].tv_usec = ts[1].tv_nsec / 1000;

    char fpath[1000];
    strcpy(toBeSolved, path);
    ChiperSolve(0);
    sprintf(fpath, "%s%s", dirpath, solved);
    Reset();

    res = utimes(fpath, tv);
    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;

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

    res = lstat(fpath, stbuf);

    if (res == -1)
        return -errno;

    return res;
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
    {
        strcpy(toBeSolved, path);
        ChiperSolve(0);
        sprintf(fpath, "%s%s", dirpath, solved);
        Reset();
    }
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
        char name[1000];
        sprintf(name, "%s/%s", fpath, de->d_name);
        struct stat st;
        struct stat fstat;
        memset(&st, 0, sizeof(st));

        stat(name, &fstat);

        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;

        struct passwd *pw = getpwuid(fstat.st_uid);
        struct group *gr = getgrgid(fstat.st_gid);

        int check = 0;
        if ((strcmp(pw->pw_name, "chipset") == 0 || strcmp(pw->pw_name, "ic_controller") == 0) && strcmp(gr->gr_name, "rusak") == 0)
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
            else
                fclose(cek);
        }
        if (check == 0)
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

static int xmp_rmdir(const char *path)
{
    int res;

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

    res = rmdir(fpath);
    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_unlink(const char *path)
{
    int res;

    char fpath[1000];
    strcpy(toBeSolved, path);
    ChiperSolve(0);
    sprintf(fpath, "%s%s", dirpath, solved);
    Reset();

    char backPath[1000];
    strcpy(toBeSolved, "/Backup/");
    ChiperSolve(0);
    sprintf(backPath, "%s%s", dirpath, solved);
    Reset();

    DIR *backUp;
    backUp = opendir(backPath);
    if (backUp != NULL)
    {
        char recycle[1000];
        strcpy(toBeSolved, "/Recycle/");
        ChiperSolve(0);
        sprintf(recycle, "%s%s", dirpath, solved);
        Reset();

        DIR *recDir;
        recDir = opendir(recycle);
        if (recDir == NULL)
        {
            mkdir(recycle, 0777);
        }
        else
        {
            closedir(recDir);
        }

        char fileN[1000];
        int i = strlen(path) - 1;
        while (path[i] != '/')
        {
            i--;
        }
        i += 1;
        strcpy(fileN, &path[i]);

        char fname[1000], exten[1000];
        int x = strlen(fileN) - 1;
        if (strstr(fileN, ".") != NULL)
        {
            while (fileN[x] != '.')
            {
                x--;
            }
            strcpy(exten, &fileN[x]);
            strcpy(fname, fileN);
            fname[strlen(fname) - strlen(exten)] = '\0';
        }
        else
        {
            strcpy(fname, fileN);
            exten[0] = '\0';
        }
        
        strcpy(toBeSolved, fname);
        ChiperSolve(0);
        strcpy(fname, solved);
        Reset();
        strcpy(toBeSolved, exten);
        ChiperSolve(0);
        strcpy(exten, solved);
        Reset();

        time_t rawTime;
        time(&rawTime);
        struct tm *curTime;
        curTime = localtime(&rawTime);
        char timeSta[1000];
        sprintf(timeSta, "_%d-%d-%d_%d:%d:%d", curTime->tm_year + 1900, curTime->tm_mon + 1, curTime->tm_mday, curTime->tm_hour, curTime->tm_min, curTime->tm_sec);

        char zipName[1000];
        sprintf(zipName, "%s_deleted%s", fileN, timeSta);
        strcpy(toBeSolved, zipName);
        ChiperSolve(0);
        strcpy(zipName, solved);
        Reset();

        char zipPath[1000];
        char zipExten[100];
        strcpy(zipExten, ".zip");
        strcpy(toBeSolved, zipExten);
        ChiperSolve(0);
        strcpy(zipExten, solved);
        Reset();
        sprintf(zipPath, "%s%s%s", recycle, zipName, zipExten);

        struct dirent *de;
        while ((de = readdir(backUp)) != NULL)
        {
            if (strstr(de->d_name, fname) != NULL && strstr(de->d_name, exten) != NULL)
            {
                char sampahPath[1000];
                sprintf(sampahPath, "%s/%s", backPath, de->d_name);
                int child = fork();
                int status;
                if (child == 0)
                {
                    char *zip_argv[] = {"zip", "-m", zipPath, sampahPath, NULL};
                    execvp("zip", zip_argv);
                }
                else{
                    while(wait(&status) > 0);
                }
            }
        }
    }

    res = unlink(fpath);
    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{
    int res;

    int flag = 0;
    if (strstr(path, ".iz1") != NULL)
        flag = 1;

    if (flag == 1)
    {
        char warning[1000];
        strcpy(warning, "zenity --error --text=\"File ekstensi iz1 tidak boleh dirubah permissionnya.\n\" --title=\"Perhatian!\"");
        system(warning);
        return -1;
    }

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

    res = chmod(fpath, mode);
    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_write(const char *path, const char *buf, size_t size,
                     off_t offset, struct fuse_file_info *fi)
{
    int fd;
    int res;

    char fpath[1000];
    strcpy(toBeSolved, path);
    ChiperSolve(0);
    sprintf(fpath, "%s%s", dirpath, solved);
    Reset();

    (void)fi;
    fd = open(fpath, O_WRONLY);
    if (fd == -1)
        return -errno;

    char backPath[1000];
    strcpy(toBeSolved, "/Backup/");
    ChiperSolve(0);
    sprintf(backPath, "%s%s", dirpath, solved);
    Reset();

    DIR *backUp;
    backUp = opendir(backPath);
    if (backUp == NULL)
    {
        mkdir(backPath, 0777);
    }
    else
    {
        closedir(backUp);
    }

    res = pwrite(fd, buf, size, offset);

    int child = fork();
    if (child == 0)
    {
        char fileBack[1000];
        char srcFile[1000];
        int i = strlen(fpath) - 1;
        while (fpath[i] != '/')
        {
            i--;
        }
        i += 1;
        strcpy(fileBack, &fpath[i]);

        strcpy(srcFile, fpath);
        srcFile[strlen(srcFile) - (strlen(fileBack))] = '\0';

        strcat(srcFile, fileBack);

        strcpy(toBeSolved, fileBack);
        ChiperSolve(1);
        strcpy(fileBack, solved);
        Reset();

        if (strstr(fileBack, ".") != NULL)
        {
            char newName[1000], exten[1000];
            int x = strlen(fileBack) - 1;
            while (fileBack[x] != '.')
            {
                x--;
            }
            strcpy(exten, &fileBack[x]);
            strcpy(newName, fileBack);
            newName[strlen(newName) - strlen(exten)] = '\0';

            time_t rawTime;
            time(&rawTime);
            struct tm *curTime;
            curTime = localtime(&rawTime);

            char temp[1000];
            sprintf(temp, "_%d-%d-%d_%d:%d:%d", curTime->tm_year + 1900, curTime->tm_mon + 1, curTime->tm_mday, curTime->tm_hour, curTime->tm_min, curTime->tm_sec);

            strcat(newName, temp);
            strcat(newName, exten);

            strcpy(fileBack, newName);
        }
        else
        {
            time_t rawTime;
            time(&rawTime);
            struct tm *curTime;
            curTime = localtime(&rawTime);

            char temp[1000];
            sprintf(temp, "_%d-%d-%d_%d:%d:%d", curTime->tm_year + 1900, curTime->tm_mon + 1, curTime->tm_mday, curTime->tm_hour, curTime->tm_min, curTime->tm_sec);
            strcat(fileBack, temp);
        }

        strcpy(toBeSolved, fileBack);
        ChiperSolve(0);
        strcpy(fileBack, solved);
        Reset();

        char destFile[1000];
        sprintf(destFile, "%s%s", backPath, fileBack);

        char *argv[] = {"cp", srcFile, destFile, NULL};
        execvp("cp", argv);
    }

    if (res == -1)
        res = -errno;

    close(fd);
    return res;
}

static int xmp_open(const char *path, struct fuse_file_info *fi)
{
    int res;

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

    res = open(fpath, fi->flags);
    if (res == -1)
        return -errno;

    close(res);
    return 0;
}

static int xmp_chown(const char *path, uid_t uid, gid_t gid)
{
    int res;

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

    res = lchown(fpath, uid, gid);
    if (res == -1)
        return -errno;

    return 0;
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
