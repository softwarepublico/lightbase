		Como usar as classes de LIFILE

	Esta DLL contem classes para tratamento de arquivo, que sao 
assim distribuidas:

- C_File		-> tratamento de arquivo em "baixo nivel". Nao possui
					conceito de registros, nem de header. Eh um stream.
- C_RecordFile	-> tratamento de arquivo que possui registros de
					tamanho fixo e um header. 
- C_DynamicFile	-> tratamento de arquivo com registros de tamanho
					variavel (lista de blocos).


	C_RecordFile e C_DynamicFile sao derivadas de C_File.

	A seguir, estao descritos os principais metodos de cada uma das
classes:

C_File
------

	C_File()
		- construtor vazio. nao faz nada com o arquivo.
			simplesmente inicializa as estruturas internas.
			Eh necessario usar o metodo Open para abrir o
			arquivo.
	C_File( const char *szNameFile, const char *szModePar, int iShFlagPar, BOOL bWait )
		- construtor numero 2. Inicializa o objeto e chama o metodo Open.

	Open( const char *szNameFile, const char *szModePar, int iShFlagPar, BOOL bWait )
		- abre (ou cria) um arquivo.
		- szNameFile = nome completo do arquivo
		- szModePar = modo de abertura (aqueles velhos conhecidos "rw", "a+", etc.)
		- iShFlagPar = flags de compartilhamento. para ver os possiveis
						valores, consulte help sobre _SH_DENYRW
		- bWait = indica se o metodo Open deve esperar que o arquivo esteja
				  disponivel para poder abri-lo. Pode acontecer de o metodo 
				  nao conseguir abrir o arquivo porque ha' outro processo
				  usando o dito cujo em modo exclusivo. Se bWait for TRUE,
				  o metodo Open espera um segundo e tenta novamente. Ele fica
				  em loop ate' conseguir abrir. Ou seja, NAO HA' TIME-OUT.
		- retorna OK ou !OK.

	Write( void FAR *buffer, size_t size )
		- chama o metodo Write abaixo.
		- retorna OK ou !OK.

	Write( void FAR *pvBuf, size_t tsSize, size_t tsNumItens )
		- escreve um buffer no arquivo.
		- retorna o numero de itens (indicado por tsNumItens) gravados.

	Read( void FAR *buffer, size_t size )
		- chama o metodo Read abaixo
		- retorna OK ou !OK

	Read( void FAR *pvBuf, size_t tsSize, size_t tsNumItens )
		- le^ um buffer do arquivo (pvBuf ja deve estar alocado)
		- retorna o numero de itens lidos

	ReadBuffer( void FAR *pvBuf, size_t tsSize )
		- le^ um buffer do arquivo ateh o fim do arquivo ou o
		  fim do buffer
		- retorna o numero BYTES lidos ou -1 em caso de erro.

	Seek( long lOffset, int iWhence )
		- realiza um posicionamento no arquivo.
		- lOffser = deslocamento
		- iWhence = SEEK_SET, SEEK_CUR ou SEEK_END

	Lock( long lSize )
		- trava uma porcao do arquivo, compreendida entre a posicao
		  corrente e ela mais lSize.

	Release( long lSize )
		- destrava uma porcao do arquivo.

	FileSize()
		- retorna o tamanho (em bytes) do arquivo.

	CurPos()
		- retorna a posicao corrente do arquivo.


	Consulte o filecl.h para ver se ha' mais metodos que lhe sejam
	interessantes.

C_RecordFile
------------

	C_RecordFile( BYTE bMagicNumberPar )
		- construtor 1. Recebe o numero magico do arquivo e inicializa
		  as estruturas internas.

	C_RecordFile( char* szFileNamePar, BYTE bMagicNumberPar, long lHeadSize, long lRecSize,
					char *szHeadKey, char *szRecKey,
					const char *szMode, int iShFlag )
		- construtor 2.
		- bMagicNumberPar = numero magico do arquivo.
		- chama o metodo Open

	Open( char* szFileNamePar, long lHeadSize, long lRecSize,
			char *szHeadKey, char *szRecKey,
			const char *szMode, int iShFlag )
		- szFileNamePar = nome completo do arquivo.
		- lHeadSize = tamanho do header do arquivo.
		- lRecSize = tamanho de um registro
		- szHeadKey = chave de criptografia para o cabecalho (usada pelo
						esquema de criptografia interno). Deve ser NULL
						para a classe NAO realizar criptografia.
		- szRecKey = chave de criptografia dos registros.
		- szMode = modo de abertura (ver C_File)
		- iShFlag = flags de compartilhamento (ver C_File)

	R_Seek( long lPos )
		- seek a nivel de registros (comecando em 0)

	R_SeekNext( void )
		- posiciona-se no proximo registro

	R_SeekPrevious( void )
		- vai para o registro anterior

	R_Write( void *szBuffer )
		- escreve um registro

	R_Append( void *szBuffer )
		- adiciona um registro no arquivo

	R_Read( void *szBuffer )
		- le^ um registro. szBuffer deve estar alocado.

	R_WriteHead( void *szBuffer )
		- grava o header do arquivo.

	R_ReadHead( void *szBuffer )
		- le^ o header do arquivo.

	R_FileSize( void )
		- obtem o tamanho do arquivo (em numero de registros)

	R_CurPos( void )
		- obtem o numero do registro corrente.

	R_Lock( void )
		- trava o registro corrente

	R_Release( void )
		- destrava o registro corrente

	R_LockHead( void )
		- trava o header

	R_ReleaseHead( void )
		- destrava o header


C_DynamicFile
-------------

	Nesta classe existe uma variavel publica, de nome cdfhHead, que representa
	o cabecalho do arquivo. Esse cabecalho eh um numero magico seguido
	da cabeca da lista de buracos livres.

	C_DynamicFile( BYTE bMagicNumberPar )
		- primeiro construtor. recebe o numero magico e inicializa
		  as estruturas internas.

	C_DynamicFile( char *szFileName, BYTE bMagicNumberPar, char *szKeyPar,
					const char *szMode, int iShFlag )
		- segundo construtor.
		- bMagicNumber = numero magico do arquivo.
		- chama o metodo Open.

	Open( char *szFileName, BYTE bMagicNumberPar, char *szKeyPar,
			const char *szMode, int iShFlag )
		- szFileName = nome completo do arquivo.
		- szKeyPar = chave de criptografia do arquivo.
		- szMode = modo de abertura do arquivo.
		- iShFlag = flag de compartilhamento do arquivo.

	D_WriteOnFreeSpace( void *szBuffer, long lLen )
		- escreve um buffer em um lugar livre no arquivo.
		- retorna a posicao do arquivo que contem o primeiro byte
		  gravado.

	D_GetFreeSpace( long lLen )
		- obtem um espaco livre no arquivo.
		- retorna a posicao no arquivo que contem o espaco desejado.

	D_FreeSpace( long lGap, long lLen )
		- libera um espaco no arquivo.
		- lGap = posicao inicial do arquivo que sera' liberada.
		- lLen = tamanho da area liberada
		O espaco livre sera' adicionado na lista de buracos livres.
		- retorna lGap em caso de sucesso ou um valor negativo indicando
		  erro.

	WriteHead()
		- grava o header do arquivo (o header eh o num. magico + 
			a cabeca da lista de buracos livres)
		- retorna OK ou !OK

	ReadHead()
		- le^ o header do arquivo (o header eh o num. magico + 
			a cabeca da lista de buracos livres)
		- retorna OK ou !OK

	LockHead()
		- trava o header
		- retorna OK ou !OK

	ReleaseHead()
		- destrava o header
		- retorna OK ou !OK




	O esquema de criptografia utilizado nessas classes eh bastante simples
e pode ser substituido pelo seu. Basta criar uma subclasse de uma dessas
classes e implementar os metodos

	void Encrypt( void *, char *, size_t );
	void Decrypt( void *, char *, size_t );

	Esses metodos sao virtuais em C_File e, portanto, se voce implementa-los
em sua subclasse, os seus metodos eh que serao chamados.

	- o primeiro parametro eh o buffer a ser criptografado;
	- o segundo eh a chave de criptografia;
	- o terceiro eh o tamanho do buffer.


