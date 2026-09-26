#include <stdio.h>
#include <string.h>

#define MAX_PHIEU 50
#define PHI_PHAT_MOI_NGAY 5000

int main(void) {
	char maPhieu[MAX_PHIEU][20];
	int ngayQuaHan[MAX_PHIEU];
	int soLuong=3;
	
	strcpy(maPhieu[0],"PM101");
	ngayQuaHan[0]=0;
	
	strcpy(maPhieu[1], "PM102");
	ngayQuaHan[1]=3;
	
	strcpy(maPhieu[2], "PM103");
	ngayQuaHan[2]=5;
	
	int luaChon;
	int i;
	char maTimKiem[20];
	int viTriTimThay;
	int ngayMoi;
	
	do{
		printf("\n--- HE THONG QUAN LY MUON TRA SACH (LIBRARY_WMS) ---\n");
		printf("1. Xem danh sach phieu muon\n");
		printf("2. Them moi phieu muon\n");
		printf("3. Cap nhat so ngay qua han\n");
		printf("0. Thoat\n");
		printf("Chon chuc nang: ");
			
		if (scanf("%d", &luaChon) !=1) {
			printf("Loi: Vui long nhap mot chu so hop le \n");
			while (getchar()!='\n');
			continue;
		}
		while (getchar() !='\n');
		
		switch(luaChon) {
			case 1:
				printf("\n--- DANH SACH PHIEU MUON ---\n");
				printf("STT | Ma Phieu | So Ngay Qua Han | Tien Phat(VND)\n");
				printf("--------------------------------------------------\n");
				for (i = 0; i < soLuong; i++) {
					int tienPhat = ngayQuaHan[i] * PHI_PHAT_MOI_NGAY;
					printf("%-3d |  %-2d ngay      | %d VND\n ",i+1,maPhieu[i],ngayQuaHan[i],tienPhat);
				}
				printf("------------------------------------------------------------------------------\n");
				printf("Tong so phieu: %d\n, soLuong");
				break;
			case 2:
				if(soLuong >= MAX_PHIEU){
					printf("Loi:Danh sach phieu muon da day, khong the them \n");
					break;
				}
				
				printf("Nhap Ma phieu muon moi: ");
				scanf("%s", maPhieu[soLuong]);
				while(getchar() != '\n');
				
				ngayQuaHan[soLuong] = 0;
				soLuong++;
				
				printf("Them phieu muon moi thanh cong! So luong hien tai la: %d\n, soLuong");
				break;
			case 3:
				if (soLuong == 0){
					printf("Danh sach phieu muon dang trong \n");
					break;
				}
				
				printf("Nhap ma phieu muon cap nhap: ");
				scanf("%s", maTimKiem);
				while(getchar()!='\n');
				
				viTriTimThay = -1;
				for (i=0; i< soLuong; i++ ) {
					if (strcmp(maPhieu[i],maTimKiem) == 0){
						viTriTimThay = i;
						break;
					}
				}
				if(viTriTimThay == -1) {
					printf("Loi:Khong tim thay ma phieu muon '%s' trong he thong\n,maTimKiem");
				} else{
					printf("Tim thay ma phieu muon'%s' tai vi tri index %d.\n",maTimKiem,viTriTimThay);
					
					while(1){
						printf("Nhap so ngay qua han moi: ");
						if(scanf("%d",&ngayMoi)==1 && ngayMoi >=0) {
							while(getchar() != '\n');
							ngayQuaHan[viTriTimThay] = ngayMoi;
							printf("Cap nhat thanh cong! So ngay qua han moi cua %s la %d ngay \n",maTimKiem, ngayMoi);
							break;		
						}else{
							printf("Loi: so ngay qua han phai >=0. Nhap lai \n");
							while(getchar() !='\n');
						}
					}
				}
				break;
			case 0:
				printf("\n Cam on ban da su dung he thong LIBRARY_WMS \n");
				break;
				
			default:
				printf("Loi: Chuc nang khong ton tai.Vui long chon lai tu 0 den 3 \n");
				break;
		}
	}while(luaChon!=0);
	
	return 0;
}
