#include <stdio.h>

int main(void) {
    int tuoi = 0;
    int mac_phim = 0;
    int suat_chieu = 0;
    int loai_ghe = 0;
    int la_ngay_thuong = 0;
    int doi_tuong = 0;

    int gia_ve_goc = 0;
    int phu_thu_ghe = 0;
    int tien_giam = 0;
    int tong_tien = 0;
    int phan_tram_giam = 0;

    printf("=== HE THONG QUAN LY BAN VE CGV CINEMA ===\n");

    // Yeu cau 1: Kiem tra tinh hop le cua tuoi
    printf("Nhap tuoi cua khach hang: ");
    scanf("%d", &tuoi);
    if (tuoi < 0 || tuoi > 120) {
        printf("Loi: So tuoi nhap vao khong hop le!\n");
        return 0;
    }

    // Yeu cau 2: Kiem soat do tuoi theo mac phim
    printf("Nhap mac phim (1: P, 2: T16, 3: T18): ");
    scanf("%d", &mac_phim);
    if (mac_phim == 1) {
        // Phim P: Moi do tuoi deu duoc xem
    } else if (mac_phim == 2) {
        if (tuoi < 16) {
            printf("Tu choi ban ve: Phim T16 yeu cau khan gia tu 16 tuoi tro len!\n");
            return 0;
        }
    } else if (mac_phim == 3) {
        if (tuoi < 18) {
            printf("Tu choi ban ve: Phim T18 cam khan gia duoi 18 tuoi!\n");
            return 0;
        }
    } else {
        printf("Loi: Ma phan loai phim khong hop le!\n");
        return 0;
    }

    // Yeu cau 3: Dinh gia ve goc theo suat chieu (switch-case)
    printf("Nhap suat chieu (1: Sang, 2: Chieu, 3: Toi): ");
    scanf("%d", &suat_chieu);
    switch (suat_chieu) {
        case 1:
            gia_ve_goc = 70000;
            break;
        case 2:
            gia_ve_goc = 90000;
            break;
        case 3:
            gia_ve_goc = 120000;
            break;
        default:
            printf("Loi: Lua chon suat chieu khong nam trong menu!\n");
            return 0;
    }

    // Yeu cau 4: Tinh phu thu loai ghe
    printf("Nhap loai ghe (1: Thuong, 2: VIP, 3: Couple): ");
    scanf("%d", &loai_ghe);
    if (loai_ghe == 1) {
        phu_thu_ghe = 0;
    } else if (loai_ghe == 2) {
        phu_thu_ghe = 15000;
    } else if (loai_ghe == 3) {
        phu_thu_ghe = 30000;
    } else {
        printf("Loi: Loai ghe khong hop le!\n");
        return 0;
    }

    // Nhap thong tin ngay va doi tuong
    printf("Co phai ngay thuong khong? (1: Co, 0: Khong): ");
    scanf("%d", &la_ngay_thuong);

    printf("Nhap doi tuong (1: HSSV, 2: Nguoi cao tuoi, 3: Thuong): ");
    scanf("%d", &doi_tuong);

    // Yeu cau 5: Tinh chiet khau giam gia vao ngay thuong
    if (la_ngay_thuong == 1) {
        if (doi_tuong == 1) {
            phan_tram_giam = 20;
            tien_giam = (int)(gia_ve_goc * 0.20);
        } else if (doi_tuong == 2 || tuoi >= 60) {
            phan_tram_giam = 30;
            tien_giam = (int)(gia_ve_goc * 0.30);
        } else {
            phan_tram_giam = 0;
            tien_giam = 0;
        }
    } else {
        phan_tram_giam = 0;
        tien_giam = 0;
    }

    // Yeu cau 6: Tinh tong tien thanh toan cuoi cung
    tong_tien = (gia_ve_goc - tien_giam) + phu_thu_ghe;

    // Xuat hoa don chi tiet chuan
    printf("\n--------------------------------------------------\n");
    printf("              HOA DON THANH TOAN VE PHIM          \n");
    printf("--------------------------------------------------\n");

    // Thong tin khan gia
    if (mac_phim == 3) {
        printf("Khan gia            : %d tuoi (Du dieu kien xem phim T18)\n", tuoi);
    } else if (mac_phim == 2) {
        printf("Khan gia            : %d tuoi (Du dieu kien xem phim T16)\n", tuoi);
    } else {
        printf("Khan gia            : %d tuoi (Phim P - Moi do tuoi)\n", tuoi);
    }

    // Thong tin suat chieu
    if (suat_chieu == 1) {
        printf("Suat chieu          : Suat Sang (Truoc 12h)\n");
    } else if (suat_chieu == 2) {
        printf("Suat chieu          : Suat Chieu (12h - 17h)\n");
    } else {
        printf("Suat chieu          : Suat Toi / Blockbuster\n");
    }

    // Thong tin loai ghe
    if (loai_ghe == 1) {
        printf("Loai ghe            : Ghe Thuong\n");
    } else if (loai_ghe == 2) {
        printf("Loai ghe            : Ghe VIP\n");
    } else {
        printf("Loai ghe            : Ghe Couple\n");
    }

    printf("--------------------------------------------------\n");
    printf("Gia ve goc          : %d VND\n", gia_ve_goc);
    if (tien_giam > 0) {
        printf("Giam gia (%d%%)       : -%d VND\n", phan_tram_giam, tien_giam);
    }
    if (phu_thu_ghe > 0) {
        if (loai_ghe == 2) {
            printf("Phu thu ghe VIP     : +%d VND\n", phu_thu_ghe);
        } else if (loai_ghe == 3) {
            printf("Phu thu ghe Couple  : +%d VND\n", phu_thu_ghe);
        }
    }
    printf("--------------------------------------------------\n");
    printf("TONG TIEN THANH TOAN: %d VND\n", tong_tien);
    printf("--------------------------------------------------\n");

    return 0;
}
