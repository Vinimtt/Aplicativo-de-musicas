#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_MAX_PLYLST 200
#define TAM_NOME 50
#define TAM_LOGIN 15
#define TAM_SENHA 15
#define TAM_PLAYLIST 100
#define TAM_TITULO 50
#define TAM_MUSICAS 100

struct Musica {
    int codigo; // autoincremento
    char titulo[TAM_TITULO]; // título da música
    char artista[TAM_NOME]; // nome do artista que canta esta música
};

struct Playlist {
    int codigo; // autoincremento
    int codUsuario; // o código do usuário que criou a playlist
    char titulo[TAM_TITULO]; // título desta playlist
    int qtdMusicas; // qtd atual de músicas incluídas nesta playlist
    int musicas[TAM_MUSICAS]; // vetor contendo os códigos das músicas
};

struct Usuario {
    int codigo; // autoincremento
    char nome[TAM_NOME];
    char login[TAM_LOGIN];
    char senha[TAM_SENHA];
    int qtdPlaylists; // quantid. de playlists criadas pelo usuário
    struct Playlist playlists[TAM_PLAYLIST]; // todas playlists criadas
    int qtdPlaylistsFav; // quantid. de playlists favoritadas pelo usuário
    int playlistsFav[TAM_PLAYLIST]; // códigos das playlists favoritadas pelo usuário
};

int usuarioCounter = 1;
int musicaCounter = 1;
int playlistCounter = 1;

int adm(){
    while(getchar() != '\n');
    char r[TAM_SENHA];
    printf("Digite a senha para fazer login: \n");
    fgets(r,TAM_SENHA,stdin);
    while(strcmp(r,"m@st3r2024\n") != 0){
        printf("Senha errada, digite novamente!\n");
        fgets(r,TAM_SENHA,stdin);
    }
    if(strcmp(r,"m@st3r2024\n") == 0){
        return 1;      
    }
    else{
        return 0;
    }
}

void todas_infos(struct Usuario usuarios[], int i) {
    printf("Usuário %d\n", i + 1);
    printf("Codigo: %d\n", usuarios[i].codigo);
    printf("Nome: %s\n", usuarios[i].nome);
    printf("Login: %s\n", usuarios[i].login);
    printf("Quantidade de Playlists: %d\n", usuarios[i].qtdPlaylists);
    printf("Quantidade de playlists favoritas: %d\n", usuarios[i].qtdPlaylistsFav);
}

void todas_musicas(struct Musica musicas[], int i) {
    printf("Musica %d\n", i + 1);
    printf("Codigo: %d\n", musicas[i].codigo);
    printf("Titulo: %s\n", musicas[i].titulo);
    printf("Artista: %s\n", musicas[i].artista);
}

void listarUsuario(struct Usuario usuarios[], int qtdUsuarios) {
    for (int i = 0; i < qtdUsuarios; ++i) {
        todas_infos(usuarios, i);
    }
}

void menu() {
    printf("Voce deseja consultar usuario de que forma?\n");
    printf("1- Codigo\n");
    printf("2- Login\n");
    printf("3- Parte do nome\n");
}

void menu2() {
    printf("Voce deseja consultar a musica de que forma?\n");
    printf("1- Codigo\n");
    printf("2- Parte do titulo\n");
    printf("3- Parte do nome do artista\n");
}

void menu3() {
    printf("Voce deseja consultar playlist de que forma?\n");
    printf("1- Codigo da playlist\n");
    printf("2- Parte do titulo da playlist\n");
    printf("3- Codigo de musica\n");
}
void usuario(){
    printf("Informe o que voce deseja fazer\n");
    printf("1- Entrar com login\n");
    printf("2- Cadastrar\n");
}

void menu_adm(){
    printf("1- Listar usuarios\n");
    printf("2- Consultar usuario\n");
    printf("3- Alterar senha de um usuario\n");
    printf("4- Cadastrar nova musica\n");
    printf("5- Listar todas as musicas\n");
    printf("6- Consultar musicas\n");
    printf("7- Alterar musica\n");
    printf("8- Listar todas as playlits\n");
    printf("9- Consultar playlist\n");
    printf("10- Gerar dados\n");
    printf("11- Sair\n");
}

void menu_usuario(){
    printf("1- Listar seus dados\n");
    printf("2- Alterar seu nome\n");
    printf("3- Alterar seu login\n");
    printf("4- Alterar sua senha\n");
    printf("5- Listar usuarios\n");
    printf("6- Consultar um usuario\n");
    printf("7- Listar todas as musicas\n");
    printf("8- Consultar uma musica\n");
    printf("9- Listar suas playlists\n");
    printf("10- Listas todas playlists\n");
    printf("11- Criar playlist\n");
    printf("12- Sair\n");
}

void consultar_usuario(struct Usuario usuarios[],int qtdUsuarios) {
    int r;
    menu();
    scanf("%d", &r);
    while (r < 1 || r > 3) {
        printf("Opcao indisponivel, digite novamente.\n");
        scanf("%d", &r);
    }
    if (r == 1) {
        int codigo;
        printf("Digite o codigo do usuario: ");
        scanf("%d", &codigo);
        for (int i = 0; i < qtdUsuarios; ++i) {
            if (codigo == usuarios[i].codigo) {
                todas_infos(usuarios, i);
            }
        }
    } else if (r == 2) {
        char login[TAM_LOGIN];
        printf("Digite o login do usuario: ");
        while (getchar() != '\n');
        fgets(login, TAM_LOGIN, stdin);
        for (int i = 0; i < qtdUsuarios + 1; ++i) {
            if (strcmp(usuarios[i].login,login) == 0) {
                todas_infos(usuarios, i);
            }
        }
    } else {
        char nome[TAM_NOME];
        printf("Digite o nome do usuario: ");
        while(getchar() != '\n');
        fgets(nome, TAM_NOME, stdin);
        printf("%s", nome);
        for (int i = 0; i < qtdUsuarios; ++i) {
            if (strstr(usuarios[i].nome, nome) != NULL) {
                todas_infos(usuarios, i);
            }
            else{
                printf("Usuario nao encontrado\n");
            }
        }
    }
}

void confirmar_senha(struct Usuario usuarios[],int i, char verifica[]){
    if (strcmp(usuarios[i].senha, verifica) == 0) {
        printf("Senha alterada!\n");
        printf("%s",usuarios[i].senha);
    } else {
        printf("Senhas nao combinam!\n");
    }
}

void alterar_senhaADM(struct Usuario usuarios[], int qtdUsuarios) {
    int codigo;
    char verifica[TAM_SENHA];
    printf("Digite o codigo do usuario: ");
    scanf("%d", &codigo);
    for (int i = 0; i < qtdUsuarios; ++i) {
        if (codigo == usuarios[i].codigo) {
            printf("Digite a nova senha: ");
            while (getchar() != '\n');
            fgets(usuarios[i].senha, TAM_SENHA, stdin);
            printf("Confirme a nova senha: ");
            fgets(verifica, TAM_SENHA, stdin);
            confirmar_senha(usuarios, i, verifica);
        }
    }
}

void cadastrar_musica(struct Musica musicas[], int *qtdMusicas) {
    while(getchar() != '\n');
    printf("Digite o titulo da nova musica: ");
    fgets(musicas[*qtdMusicas].titulo, TAM_TITULO, stdin);
    printf("Digite o nome do artista: ");
    fgets(musicas[*qtdMusicas].artista, TAM_NOME, stdin);
    (*qtdMusicas)++;
    printf("Musica cadastrada com sucesso!\n");
}

void listar_musicas(struct Musica musicas[],int *qtdMusicas) {
    for (int i = 0; i < *qtdMusicas; ++i) {
        todas_musicas(musicas, i);
    }
}

void consultar_musica(struct Musica musicas[]) {
    int r;
    menu2();
    scanf("%d", &r);
    while (r < 1 || r > 3) {
        printf("Opcao indisponivel, digite novamente.\n");
        scanf("%d", &r);
    }
    if (r == 1) {
        int codigo;
        printf("Digite o codigo da musica: ");
        scanf("%d", &codigo);
        for (int i = 0; i < TAM_PLAYLIST; ++i) {
            if (codigo == musicas[i].codigo) {
                todas_musicas(musicas, i);
            }
        }
    } else if (r == 2) {
        char titulo[TAM_TITULO];
        printf("Digite parte do titulo da musica: ");
        while (getchar() != '\n');
        fgets(titulo, TAM_TITULO, stdin);
        for (int i = 0; i < TAM_PLAYLIST; ++i) {
            if (strstr(musicas[i].titulo,titulo) != NULL) {
                todas_musicas(musicas, i);
            }
        }
    } else {
        char nome[TAM_NOME];
        printf("Digite o nome do artista da musica: ");
        while (getchar() != '\n');
        fgets(nome, TAM_NOME, stdin);
        for (int i = 0; i < TAM_PLAYLIST; ++i) {
            if (strstr(musicas[i].artista, nome) != NULL) {
                todas_musicas(musicas, i);
            }
        }
    }
}

void alterar_musicas(struct Musica musicas[], int *qtdMusicas) {
    int codigo;
    printf("Informe o codigo da musica que deseja alterar: ");
    scanf("%d", &codigo);
    for (int i = 0; i < *qtdMusicas; ++i) {
        if (codigo == musicas[i].codigo) {
            printf("Musica: %d\n", i + 1);
            printf("Digite a nova musica:\n");
            while (getchar() != '\n');
            fgets(musicas[i].titulo, TAM_TITULO, stdin);
            printf("Digite o nome do artista:\n");
            fgets(musicas[i].artista, TAM_NOME, stdin);
        }
    }
}

void todas_playlits(struct Playlist playlists[], struct Usuario usuarios[], struct Musica musicas[], int i) {
    printf("Playlist %d\n", i + 1);
    printf("Codigo: %d\n", playlists[i].codigo);
    printf("Titulo: %s\n", playlists[i].titulo);
    printf("Criador: %s\n", usuarios[playlists[i].codUsuario - 1].nome);
    for (int j = 0; j < playlists[i].qtdMusicas; ++j) {
        printf("Musica %d: %s\n", j + 1, musicas[playlists[i].musicas[j]].titulo);
    }
    printf("\n");
}

void listar_playlists(struct Playlist playlists[], struct Usuario usuarios[], struct Musica musicas[],int qtdPlaylists) {
    for (int i = 0; i < qtdPlaylists; ++i) {
        todas_playlits(playlists, usuarios, musicas, i);
    }
}

void consultar_playlist(struct Playlist playlists[], struct Usuario usuarios[], struct Musica musicas[]) {
    int r;
    menu3();
    scanf("%d", &r);
    while (r < 1 || r > 3) {
        printf("Opcao indisponivel, digite novamente.\n");
        scanf("%d", &r);
    }
    if (r == 1) {
        int codigo;
        printf("Digite o codigo da playlist: ");
        scanf("%d", &codigo);
        for (int i = 0; i < TAM_PLAYLIST; ++i) {
            if (codigo == playlists[i].codigo) {
                todas_playlits(playlists, usuarios, musicas, i);
            }
        }
    } else if (r == 2) {
        char titulo[TAM_TITULO];
        printf("Digite parte do titulo da playlist: ");
        while (getchar() != '\n');
        fgets(titulo, TAM_TITULO, stdin);
        for (int i = 0; i < TAM_PLAYLIST; ++i) {
            if (strstr(titulo, playlists[i].titulo) != NULL) {
                todas_playlits(playlists, usuarios, musicas, i);
            }
        }
    } else {
        int codigo;
        printf("Digite o codigo da musica: ");
        scanf("%d", &codigo);
        for (int i = 0; i < TAM_PLAYLIST; ++i) {
            for (int j = 0; j < playlists[i].qtdMusicas; ++j) {
                if (codigo == playlists[i].musicas[j]) {
                    printf("Playlist %d\n", i + 1);
                    printf("Codigo: %d\n", playlists[i].codigo);
                    printf("Titulo: %s\n", playlists[i].titulo);
                    printf("Criador: %s\n", usuarios[playlists[i].codUsuario - 1].nome);
                    for (int k = 0; k < playlists[i].qtdMusicas; ++k) {
                        printf("Musica %d: %s\n", k + 1, musicas[playlists[i].musicas[k]].titulo);
                    }
                    printf("\n");
                }
            }
        }
    }
}

void cadastrar_usuario(struct Usuario usuarios[], int *qtdUsuarios){
    while(getchar() != '\n');
    char senha[TAM_SENHA];
    printf("Informe o nome do usuario: ");
    fgets(usuarios[*qtdUsuarios].nome, TAM_NOME, stdin);
    printf("Informe o login do usuario: ");
    fgets(usuarios[*qtdUsuarios].login,TAM_LOGIN,stdin);
    printf("Informe a senha do usuario: ");
    fgets(usuarios[*qtdUsuarios].senha,TAM_SENHA,stdin);
    printf("Informe novamente a senha: ");
    fgets(senha,TAM_SENHA,stdin);
    while(strcmp(usuarios[*qtdUsuarios].senha,senha) != 0){
        printf("Senhas nao combinam, digite novamente: ");
        fgets(senha,TAM_SENHA,stdin);
    }
    if(strcmp(usuarios[*qtdUsuarios].senha,senha) == 0){
        usuarios[*qtdUsuarios].codigo = usuarioCounter++;
        usuarios[*qtdUsuarios].qtdPlaylists = 0;
        usuarios[*qtdUsuarios].qtdPlaylistsFav = 0;
        (*qtdUsuarios)++;
    }

    
}

void login_usuario(struct Usuario usuarios[], int qtdUsuarios, int *posicaoAtual) {
    while(getchar() != '\n');
    char login[TAM_LOGIN], senha[TAM_SENHA];
    printf("Digite o login do usuario:\n");
    fgets(login, TAM_LOGIN, stdin);
    printf("Digite a senha do usuario:\n");
    fgets(senha, TAM_SENHA, stdin);
    for(int i = 0; i < qtdUsuarios; ++i) {
        if(strcmp(usuarios[i].login, login) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            printf("Login bem sucedido!\n");
            *posicaoAtual = i;
            return;
        }
    }
    printf("Login nao encontrado!\n");
}


void cadastrar_playlist(struct Playlist playlists[],struct Usuario usuarios[],int *qtdPlaylists, int codUsuario) {
    if(usuarios[codUsuario].qtdPlaylists >= TAM_PLAYLIST){
        printf("Você atingiu o limite máximo de playliys na sua conta!\n");
        return;
    }
    while(getchar() != '\n');
    playlists[*qtdPlaylists].codigo = playlistCounter++;
    playlists[*qtdPlaylists].codUsuario = codUsuario;
    printf("Digite o titulo da playlist: ");
    fgets(playlists[*qtdPlaylists].titulo, TAM_TITULO, stdin);
    (*qtdPlaylists)++;
    printf("Playlist cadastrada com sucesso!\n");
}

void listar_dados(struct Usuario usuarios[],int *posicaoAtual){
    printf("Codigo: %d\n",usuarios[*posicaoAtual].codigo);
    printf("Nome: %s\n",usuarios[*posicaoAtual].nome);
    printf("Login: %s\n",usuarios[*posicaoAtual].login);
    printf("Quantidade de playlists: %d\n",usuarios[*posicaoAtual].qtdPlaylists);
    printf("Quantidade de playlists favoritas: %d\n",usuarios[*posicaoAtual].qtdPlaylistsFav);

}

void alterar_nome(struct Usuario usuarios[],int *posicaoAtual){
    char nome[TAM_NOME],senha[TAM_SENHA];
    while(getchar() != '\n');
    printf("Confirme sua senha para prosseguir: \n");
    fgets(senha, TAM_SENHA, stdin);
    while(strcmp(usuarios[*posicaoAtual].senha,senha) != 0){
        printf("Senhas nao combinam!\n");
        fgets(senha,TAM_SENHA,stdin);
    }
    if(strcmp(usuarios[*posicaoAtual].senha,senha) == 0){
        printf("Informe o novo nome de usuario: \n");
        fgets(nome,TAM_NOME,stdin);
        strcpy(usuarios[*posicaoAtual].nome,nome);
        printf("%s",usuarios[*posicaoAtual].nome);
    }
}

void alterar_login(struct Usuario usuarios[],int *posicaoAtual){
    char login[TAM_LOGIN],senha[TAM_SENHA];
        while(getchar() != '\n');
        printf("Confirme sua senha para prosseguir: \n");
        fgets(senha, TAM_SENHA, stdin);
        while(strcmp(usuarios[*posicaoAtual].senha,senha) != 0){
            printf("Senhas nao combinam!\n");
            fgets(senha,TAM_SENHA,stdin);
        }
        if(strcmp(usuarios[*posicaoAtual].senha,senha) == 0){
            printf("Informe o novo login de usuario: \n");
            fgets(login,TAM_LOGIN,stdin);
            strcpy(usuarios[*posicaoAtual].login,login);
            printf("%s",usuarios[*posicaoAtual].login);
        }
}

void alterar_senha(struct Usuario usuarios[],int *posicaoAtual){
    char novaSenha[TAM_SENHA],senha[TAM_SENHA];
        while(getchar() != '\n');
        printf("Confirme sua senha para prosseguir: \n");
        fgets(senha, TAM_SENHA, stdin);
        if(strcmp(usuarios[*posicaoAtual].senha,senha) == 0){
            printf("Informe a nova senha de usuario: \n");
            fgets(novaSenha,TAM_SENHA,stdin);
            printf("Confirme a senha:\n");
            fgets(senha,TAM_SENHA,stdin);
            if(strcmp(novaSenha,senha) == 0){
                printf("Senha alterada!\n");
                strcpy(usuarios[*posicaoAtual].senha,novaSenha);
                printf("%s",usuarios[*posicaoAtual].senha);
            }
            else{
                printf("Senha incorreta!\n");
            }
        }
        else{
            printf("Senha incorreta!\n");
        }
    }

void listar_usuarioss(struct Usuario usuarios[], int qtdUsuarios){
    for(int i = 0; i < qtdUsuarios; ++i){
        printf("Usuario %d\n",i + 1);
        printf("Nome: %s\n",usuarios[i].nome);
    }
}

void consultar_usuariou(struct Usuario usuarios[], int qtdUsuarios){
    char r[TAM_NOME];
    while(getchar() != '\n');
    printf("Digite o nome do usuario: ");
    fgets(r,TAM_NOME,stdin);
    for(int i = 0; i < qtdUsuarios; ++i){
        if(strstr(usuarios[i].nome,r) != NULL){
            printf("Nome: %s\n",usuarios[i].nome);
        }
        else{
            printf("Nome nao encontrado!\n");
        }
    }
}

void listar_suas_playlists(struct Playlist playlists[], int qtdPlaylists, int codUsuario,struct Usuario usuarios[], struct Musica musicas[]){
    for(int i = 0; i < qtdPlaylists; ++i){
        if(playlists[i].codUsuario == codUsuario){
            printf("Playlist %d\n",i + 1);
            listar_playlists(playlists,usuarios,musicas,qtdPlaylists);
        }
    }
}   

void gerar_dados(struct Usuario usuarios[], struct Musica musicas[], int *qtdUsuarios, int *qtdMusicas) {
    usuarios[*qtdUsuarios].codigo = usuarioCounter++;
    strcpy(usuarios[*qtdUsuarios].nome, "vinicius");
    strcpy(usuarios[*qtdUsuarios].login, "vt");
    strcpy(usuarios[*qtdUsuarios].senha, "vini2024");
    (*qtdUsuarios)++;
    musicas[*qtdMusicas].codigo = musicaCounter++;
    strcpy(musicas[*qtdMusicas].titulo, "algum ritmo");
    strcpy(musicas[*qtdMusicas].artista, "gilsons");
    (*qtdMusicas)++;
}

int main() {
    int qtdUsuarios = 0,qtdMusicas = 0,qtdPlaylists = 0,rLogin = 0,posicaoAtual = 0;
    struct Usuario usuarios[qtdUsuarios];
    struct Musica musicas[TAM_MUSICAS];
    struct Playlist playlists[TAM_PLAYLIST];
    printf("Você deseja entrar como administrador ou usuário? (1 para administrador e 2 para usuário) ");
    scanf("%d",&rLogin);
    while(rLogin < 1 || rLogin > 2){
        printf("Valor inválido, informe novamente!\n");
        scanf("%d",&rLogin);
    }
    switch(rLogin)
        {
            case 1: 
                if(adm() == 1){
                int r,rodarADM = 1;
                while(rodarADM){
                    printf("Informe o que voce deseja fazer\n");
                menu_adm();
                scanf("%d",&r);
                switch(r){
                    case 1: 
                        listarUsuario(usuarios,qtdUsuarios);
                        break;
                    case 2:
                        consultar_usuario(usuarios,qtdUsuarios);
                        break;
                    case 3:
                        alterar_senhaADM(usuarios,qtdUsuarios);
                        break;
                    case 4:
                        cadastrar_musica(musicas,&qtdMusicas);
                        break;
                    case 5:
                        listar_musicas(musicas,&qtdMusicas);
                        break;
                    case 6:
                        consultar_musica(musicas);
                        break;
                    case 7:
                        alterar_musicas(musicas,&qtdMusicas);
                        break;
                    case 8:
                        listar_playlists(playlists,usuarios,musicas,qtdPlaylists);
                        break;
                    case 9:
                        consultar_playlist(playlists,usuarios,musicas);
                        break;
                    case 10:
                        gerar_dados(usuarios,musicas,&qtdUsuarios,&qtdMusicas);
                        break;
                    case 11:
                        rodarADM = 0;
                        break;
                }
        }    
                }
            
            else{
                printf("Senha invalida!\n");
            }
        case 2:
            usuario();
            int q;
            scanf("%d",&q);
            switch(q){
                case 1:
                    login_usuario(usuarios,qtdUsuarios,&posicaoAtual);
                    int t;
                    int rodarU = 1;
                    while(rodarU){
                            while(t != 0){
                                menu_usuario();
                                scanf("%d",&t);
                                    switch(t){
                                        case 1:
                                            listar_dados(usuarios,&posicaoAtual);
                                            break;
                                        case 2:
                                            alterar_nome(usuarios,&posicaoAtual);
                                        case 3:
                                            alterar_login(usuarios,&posicaoAtual);
                                            break;
                                        case 4:
                                            alterar_senha(usuarios,&posicaoAtual);
                                            break;
                                        case 5:
                                            listar_usuarioss(usuarios, qtdUsuarios);
                                            break;
                                        case 6:
                                            consultar_usuariou(usuarios,qtdUsuarios);
                                            break;
                                        case 7:
                                            listar_musicas(musicas,&qtdMusicas);
                                            break;
                                        case 8:
                                            consultar_musica(musicas);
                                            break;
                                        case 9:
                                            listar_suas_playlists(playlists,qtdPlaylists,qtdUsuarios,usuarios,musicas);
                                            break;
                                        case 10:
                                            listar_playlists(playlists,usuarios,musicas, qtdPlaylists);
                                            break;
                                        case 11:
                                            cadastrar_playlist(playlists,usuarios, &qtdPlaylists, qtdUsuarios);
                                            break;
                                        case 12:
                                            rodarU = 0;
                                            break;
                                    }
                                    break;
                                }
                    }
                    
                case 2:
                    cadastrar_usuario(usuarios,&qtdUsuarios);
                    int g;
                    int rodarU2 = 1;
                    while(rodarU2){
                            while(g != 0){
                                menu_usuario();
                                scanf("%d",&g);
                                    switch(g){
                                        case 1:
                                            listar_dados(usuarios,&posicaoAtual);
                                            break;
                                        case 2:
                                            alterar_nome(usuarios,&posicaoAtual);
                                            break;
                                        case 3:
                                            alterar_login(usuarios,&posicaoAtual);
                                            break;
                                        case 4:
                                            alterar_senha(usuarios,&posicaoAtual);
                                            break;
                                        case 5:
                                            listar_usuarioss(usuarios, qtdUsuarios);
                                            break;
                                        case 6:
                                            consultar_usuariou(usuarios,qtdUsuarios);
                                            break;
                                        case 7:
                                            listar_musicas(musicas,&qtdMusicas);
                                            break;
                                        case 8:
                                            consultar_musica(musicas);
                                            break;
                                        case 9:
                                            listar_suas_playlists(playlists,qtdPlaylists,qtdUsuarios,usuarios,musicas);
                                            break;
                                        case 10:
                                            listar_playlists(playlists,usuarios,musicas, qtdPlaylists);
                                            break;
                                        case 11:
                                            cadastrar_playlist(playlists,usuarios, &qtdPlaylists, qtdUsuarios);
                                            break;
                                        case 12:
                                            rodarU2 = 0;
                                            break;
                                            
                                    }
                                    break;
                                }
                    }
                
            }
            
        }

    
}
