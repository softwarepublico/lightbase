/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o 
título "LICENCA.txt", junto com este programa, se não, escreva para a Fundação do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#ifndef _BUILD_H
#define _BUILD_H

//
// class bstring is used throughout the BUILD program to manipulate
// various strings.  I would rather use ANSI standard strings, but
// they aren't widely supported yet, so I had to build my own.
//
// This class has a couple of filename functions thrown in as well.
//

class bstring {
    public :
        bstring( const char *init = "" );
        bstring( const bstring& );
        ~bstring();
        bstring& operator = ( const bstring& );
        bstring& operator = ( const char * );
        bstring operator + ( const char * );
        bstring operator + ( const bstring&  );
        int operator != ( const bstring& );
        int operator != ( const char * );
        int operator == ( const bstring& );
        int operator == ( const char * );
        operator const char *() const { return string; }
        int operator[]( int ) const;
        int index_from_end( int index ) const;
        int first( char );
        int first( const char * );
        int last( char );
        int length(){ return strlen( string ); }
        int remove_after( int );
        int remove_before( int );
        bstring get_first_token( const char *delimiters = " ," );
        bstring get_next_token( const char *delimiters = " ," );
        bstring drive() const;    // Returns "C:" or ""
        bstring path() const;     // Returns "\\comp1\\comp2\\" or ".\\"
        bstring name() const;     // Returns "name" or ""
        bstring ext() const;      // Returns ".ext" or ""
        bstring& upper();
    protected :
        char *string;
        char *tokenizer;
};

//
// class item holds a single tag and its associated value (plus optionally
// an executable file name.)  This class should properly be a nested class
// of class options, but since not all of our compilers support nested
// classes yet there is no point.  In any case, BUILD doesn't do anything
// with this class, it relies on the member functions of class options 
// to deal with it.
//
class options;
class item {
    friend class options;
    public :
        item( char *name ) : name( name ), value(), exec_file() {;}
        item *get_next_item(){ return next_item; }
        bstring name;
        bstring value;
        bstring exec_file;
    protected :
        item *next_item;
};

//
// The options class contains all the options read in from the command
// line, as well as the BUILD.INI file.  The two command line options
// are dry_run and model.  The tags out of the BUILD.INI file all get
// stuffed into a linked list of class item.
//
class options {
    public :
        options( char *first, ... );
        bstring *find_value( const char *tag );
        bstring *look_up_exec_file( const char *tag );
        bstring model;
        bstring ini_file;
        int dry_run;
        int keep_files;
        int build_demo;
        item *get_first_item(){ return first_item; }
        void erase_values();
    protected :
        item *first_item;
};

//
// class file_list contains a linked list of file names.  The file
// names themselves go in these file_name_item objects.  This should
// also be a nested class, BUILD should never dink with it, only the
// file_list class.
//
class file_name_item {
    public :
        bstring file_name;
        file_name_item *next_item;
        file_name_item( const char *s ) : file_name( s ){ next_item = 0; }
};

//
// The file_list class is used to hold the list of files that
// BUILD is going to compile.
//
class file_list {
    public :
        file_list(){ first_file = 0; }
        void add_file( const char *name );
        bstring *get_first_file();
        bstring *get_next_file();
    protected :
        file_name_item *first_file;
        file_name_item *current_item;
};

//
// Function prototypes for various guys that show up in BUILD.CPP.
//
int parse_args( int &argc, char **&argv, options &opts );
void dump_sections( options &opts );
int read_ini_file( options &opts );
int build_file_list( int argc, char **argv, file_list &files, options& opts );
int build_demo_file_list( int argc, char **argv, file_list &files );
void dump_options( options &opts );
void build_config_files( options &opts, file_list &files );
int compile_files( options &opts, file_list &files );
int compile_demo_files( options &opts, file_list &files );
int build_library( options &opts );
int link_dll( options &opts );
int cleanup( file_list &files, options &opts );
enum SECTION_TYPE { NORMAL, HIDDEN, NONE };
SECTION_TYPE get_next_section( bstring &section, fstream &file );
int read_options( options &opts, fstream &file );
int parse_option( options &opts, bstring &line );
void add_wild_cards( file_list &files, const bstring &wild_spec );
int build_config_file( options &opts,
                       const char *config_filename,
                       const char *subject_filename,
                       const bstring option_tag );
int build_lib_cmd( options &opts, file_list &files );
int object_file_exists( const bstring &file );
int execute( bstring &executable, bstring &command, int dry_run );
int exist( const bstring &s );
bstring find_executable( const bstring &s );

#endif //#ifndef _BUILD_H
