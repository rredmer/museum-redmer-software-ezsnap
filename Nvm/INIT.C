#pragma comment(lib,"init.lib")
extern char img_chk;
extern char conq_siz;
extern char ramcfg;
extern char csr_siz;
extern char view_ang;
extern char inact_to;
extern char charge;
extern char spk_vol;

void * _based(_segname("_CODE")) func_adr[] = { &img_chk, &conq_siz, &ramcfg, &csr_siz,
				 &view_ang, &inact_to, &charge, &spk_vol };

unsigned int _based(_segname("_CODE")) tbl_size = sizeof(func_adr) / sizeof(void *);

unsigned int _based(_segname("_CODE")) user_start_flag = 3;

unsigned char _based(_segname("_CODE")) func_num[] = {  0x00,  0x11,  0x01,  0x22,
				  0x25,  0x44,  0x81,  0x83 };

unsigned int _based(_segname("_CODE")) param[] = { 0, 100, 160, 160,
				 64, 0, 4, 180,
				 1, 1 };

unsigned int _based(_segname("_CODE")) index[] = { 0, 1, 2, 5,
				 6, 7, 8, 9 };

