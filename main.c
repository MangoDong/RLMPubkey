#define  _CRT_SECURE_NO_WARNINGS
#include "rlmpubkey.h"
#include <Windows.h>
#include "resource.h"

int replacepubkey(PubkeyInfo* pki);
int createsign(PubkeyInfo* pki, char* rlmsign, char* ISV);
PubkeyInfo* init();
int listFiles(char* dir, PubkeyInfo* pki);

int help() 
{
	printf("ʹ��˵��\n");
	printf("RLM 12�°汾 RLM_ISV_NAME ���������أ���Ҫ�Լ�ͨ������ļ�ȥ����\n");
	
	printf("RLMpubkey.exe ISV\n");
	printf("���磺һ������ļ���������,ISV Ϊdemo������Ϊ \"RLMpubkey.exe demo\"\n");
	printf("HOST THIS_HOST 68f7283e08b7 \nISV demo \nLICENSE demo f1 15.1 permanent 1 hostid = 68f7283e08b7 ...\n");
	printf("\n\n\n###########���ߣ�xiaolei ###########\n");
	return 0;
}

int freelist(PubkeyInfo* pki)
{
	PubkeyInfo* tmp =pki->next,*tmq;
	for (; tmp != NULL;)
	{
		tmq = tmp;
		tmp = tmp->next;
		free(tmq);
	}
	return 1;
}

int main(int argc, char* argv[])
{
	//if (argc ==1 || argc >2 )
	//{
	//	help();
	//	return 0;
	//}

	PubkeyInfo* pfirst = init();
	/*������Ҫ�滻�Ĺ�Կ����*/
	listFiles(localdir, pfirst);
	if (pfirst->next ==NULL)
	{
		printf("û����Ҫ�滻���ļ�������˳�\n");
		return 0;
	}
	/*�滻�ļ���Կ*/
	replacepubkey(pfirst);
	/*rc ��Դ����*/
	HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_EXE1), TEXT("EXE"));
	DWORD dwSize = SizeofResource(NULL, hRsrc);
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
	LPVOID pBuffer = LockResource(hGlobal);
	/**/
	//createsign(pfirst, (unsigned char *)pBuffer, argv[1]);
	createsign(pfirst, (unsigned char*)pBuffer, "izero");
	FreeResource(hGlobal);
	freelist(pfirst);
	return 1;
}