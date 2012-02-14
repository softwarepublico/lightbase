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


#define ROOT_DIR "..\\"
//  Lots of changes to BUILD.CPP.  First, I added the template
//  capability.  You can now define a library template, which is
//  shared among multiple libraries.  For example, to build DOS
//  libraries, I have a single DOS template which is shared among
//  S, SD, C, ...etc.  The include the template by using the
//  the new identifier Template=xxx.  Template definitions start
//  usually have a "." right before the name, which prevents them
//  from being displayed when sections are being dumped.
//
//  The second major change in this release of BUILD is the addition
//  of format specifiers to the keywords.  It used to be that you
//  could put %s in a command line, and BUILD would substitute the
//  filename.  It still does that, but now you can put %m for the model
//  letter in lower case, %M for upper case, %p for the file path and
//  drive, %n for the name, and %l for the library name.
//
//  The third major change is the addition of the BUILDDEMO capability.
//  Each library now has a Demo identifier, which allows BUILD
//  to create demo programs using that library.
//
//  A minor feature change is that most commands can now appear multiple
//  times in a section.  Each multiple appearance of a command is
//  tacked on to the previous ones.  When it comes time to execute the
//  commands, they are done one at a time.  This is real useful for
//  building demos that require a compile/rc/link sequence.  See the INI
//  file for details on how this works.
//
//  The Linker line now accepts multiple commands, which need
//  to be separated by the caret character: ^.  Because of this,
//  all BUILD.INI files will need to be modified to perform
//  an explicit IMPLIB.
//
// May 18, 1994   2.0
//
// This is a completely new version of the Greenleaf Build program.
// It has the same syntax as the previous version, and works mostly
// the same way.  The major changes are:
//
//   o  This version of BUILD will create DLLs and Import Libraries
//
//   o  Instead of hardcoding the information in BUILD.C, this version
//      of BUILD reads all of its information out of BUILD.INI.
//
// One of the major constraints on BUILD 1.0 was that it was required
// to have as small a memory footprint as possible.  That is why so
// much of the program was hardcoded instead of flexible.  Now, all of
// our compilers use DOS Extenders, so we don't care any more how
// much memory we take up.  This version of BUILD is the result.
//
// Much of the functionality in this version of BUILD is found into
// the bstring [Build String] class.  Some day we may be able to use a
// standard ANSI string class, but that does not exist yet.

//
// The rules:  All of the information needed by the linker is stored
//             in BUILD.INI.  The data in BUILD.INI is used to generate
//             CPP.CMD and LINKER.CMD (and others).  LIB.CMD is generated
//             using a list of file names.
//
// "BUILD ?" will create the CMD files, and not delete them
// afterwards.  You have to delete them yourself.
//
// "BUILD -keep" will leave the objects around even if the library
// builds properly.
//
// "BUILD -demo" builds demos and examples
//

#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <errno.h>
#include <conio.h>
#if defined( __WATCOMC__ )
#include <io.h> // Had to get unlink from here...
#endif
#include <ctype.h>
#include "build.h"

//
// int main( int argc, char *argv[] )
//
// ARGUMENTS
//
//  argc    : The number of arguments being passed on the command line.
//
//  argv    : The strings containing the arguments.
//
// RETURNS
//
//  0 if all files were built, and everything else ran without error.
//  1 if anything bad happened along the way.
//
// DESCRIPTION
//
//  The main routine just dispatches the functions that do all the work
//  for the build.  It checks the return codes from all the functions
//  to see if an error has occurredd.  An error at any point will 
//  stop the process.
//
//  The process goes like this:
//
//        Read in build parameters
//        Expand wild cards to make the list of files to process
//        Build config files for all compilers, linkers, etc.
//        Show the user what you are about to do
//
//        Build all the demo files
//
//        -or-
//
//        Compile all files in the list into object files
//        Add all the object files to the library
//        Link the dll, if that's what this is
//
//        Then
//
//        Delete objects and config files
//
//  REVISION HISTORY
//
//   May 18, 1994  2.0A   :  First release
//
//   January 5, 1955 3.0A : New release with more capabilities
//

int main( int argc, char *argv[] )
{
    file_list files;
    options opts( "Directories",
                  "Template",
                  "Cpp",         "CppOptions",
                  "C",           "COptions",
                  "Asm",         "AsmOptions",
                  "Librarian",   "LibrarianFormat",
                  "Linker",      "LinkerOptions",
                  "Description",
                  "Demo",         "DemoOptions",
                  "DeleteFiles",
                  "" );
// Symantec defaults to buffered output on cout and cerr.  Yuk.

    cout.rdbuf()->setbuf( (char*) 0, 0 );
    cerr.rdbuf()->setbuf( (char*) 0, 0 );
    if ( parse_args( argc, argv, opts ) == 0 )
        return 1;
    if ( read_ini_file( opts ) == 0 )
        return 1;
//
// If I am being asked to build demo programs, I have a different
// way of building the file list.  This is because demo programs
// and examples are expected to have full path names, whereas library
// building files are just specified as *.C or whatever
//
    if ( opts.build_demo ) {
        if ( build_demo_file_list( argc, argv, files ) == 0 )
            return 1;
    } else {
        if ( build_file_list( argc, argv, files, opts ) == 0 )
            return 1;
    }
    build_config_files( opts, files );
    dump_options( opts );
//
// Building demos is a little different than building libraries,
// so I have a separate routine to handle it.
//
    if ( opts.build_demo ) {
        if ( compile_demo_files( opts, files ) == 0 )
            return 1;
    } else {
        if ( compile_files( opts, files ) == 0 )
            return 1;
        if ( build_library( opts ) == 0 )
            return 1;
        if ( link_dll( opts ) == 0 )
            return 1;
    }
    if ( !opts.keep_files )
        cleanup( files, opts );
    return 0;
}

//
// int parse_args( int &argc, char **&argv, options &opts )
//
// ARGUMENTS:
//
//  argc      :  A reference to the argument count passed on the
//               command line.  One nice bonus of using C++ is that
//               using a reference argument makes it easy for the
//               parse routine to modify argc as it reads arguments,
//               then pass the modified value back to the calling
//               routine.
//               
//  argv      :  A reference to the pointer to the array of command
//               line arguments.  Like argc, this value gets incremented
//               as we work our way through the command line.
//
//  opts      :  A reference to the options structure used by this program.
//               This routine has the job of initializing just two members:
//               dry_run and model.
//
//
// RETURNS
//
//  1 if it is okay to keep going, 0 if a crummy command line got passed.
//
// DESCRIPTION
//
//  This routine is called to initialize three of the options used in the
//  build process.  dry_run is set if the user specifies -cmd.  keep_files
//  is set if -keep is found, and build_demo is set if the -demo
//  argument is found on the command line.  The library model is the
//  next argument, it gets stored in a member of opts, after being
//  converted to upper case.
//
//  Note also that I strip any "." character from the name of a model.
//  The "." character in the first position just prevents the model
//  name from being displayed when the dump_sections() routine is called.
//
//  After parsing the one or two arguments, argc and argv will be updated
//  so the file name parsing can start right up.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A   : First release
//
//   January 5, 1995 3.0A : Added support for the -demo option.
//

int parse_args( int &argc, char **&argv, options &opts )
{
    opts.dry_run = 0;
    opts.keep_files = 0;
    opts.build_demo = 0;
    opts.ini_file = *argv;
    int i = opts.ini_file.last( '.' );
    if ( i != -1 )
        opts.ini_file.remove_after( i - 1 );
    opts.ini_file = opts.ini_file + ".INI";
    argc--;  // go past argv[ 0 ], which is the program name
    argv++;
    while ( argc >= 1 ) {
        if ( stricmp( *argv, "-cmd" ) == 0 ) {
            opts.dry_run = 1;
            argc--;
            argv++;
        } else if ( stricmp( *argv, "-keep" ) == 0 ) {
            opts.keep_files = 1;
            argc--;
            argv++;
        } else if ( stricmp( *argv, "-demo" ) == 0 ) {
            opts.build_demo = 1;
            argc--;
            argv++;
        } else
            break;
    }
    if ( argc < 1 ) {
        cerr << "\nBuild Version 2.0A\n";
        cerr << "Copyright (c) 1994 Greenleaf Software, Inc.\n";
        cerr << "Usage: Build [-cmd] [-keep] [-demo] model [file(s)]\n\n";
        cerr << "Options:\n";
        cerr << "-cmd   create CMD files and quit\n";
        cerr << "-keep  keep OBJ and CMD files after build\n";
        cerr << "-demo  Make an example or a demo, not a library\n\n";
        cerr << "Note:  If you are building a library, you shouldn't\n";
        cerr << "       included path names for your source files.  The\n";
        cerr << "       BUILD program will look in the appropriate\n";
        cerr << "       directories for the memory model you are building.\n";
        cerr << "       Building demo files requires a path to the file.\n";
        cerr << "\nIni file = " << opts.ini_file << "\n";
        cerr << "\nHit any key to continue...";
        getch();
        cerr << "\nModels:\n";
        dump_sections( opts );
        return 0;
    }
    opts.model = *argv;
    opts.model.upper();
    argc--;
    argv++;
    return 1;
}

//
// void dump_sections( options &opts )
//
//
// ARGUMENTS:
//
//  opts       :  A refernce to the options object.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  This function is called when parse_args() determines that that user
//  didn't put anything on the command line.  All it does is blow through
//  the INI file, printing the name of each section it encounters
//  along the way.  Hidden sections are denoted by a leading ".".  They
//  don't get displayed, but they are treated as a normal section
//  at all times.
//
// REVISION HISTORY
//
//   May 19, 1994     2.0A : First release
//
//   January 5, 1995  3.0A : Added hidden sections
//

void dump_sections( options &opts )
{
    bstring section;

#ifdef __SC__
    fstream config_file( opts.ini_file, ios::in );
#else
    fstream config_file( opts.ini_file, ios::in | ios::binary );
#endif
    if ( config_file.fail() ) {
        cerr << "\nError - Could not open "
             << opts.ini_file
             << "!\n";
        return;
    }
    for ( int toggle = 0 ; ; ) {
        switch ( get_next_section( section, config_file ) ) {
            case NONE :
                return;
            case HIDDEN :
                break;
            case NORMAL :
                if ( ++toggle & 1 && toggle > 1 )
                    cerr << "\n";
// I don't know why, but with Symantec I have to do more than
// just set left, I have to clear right!!
                cerr.setf( ios::left );
                cerr.unsetf( ios::right );
                cerr.width( 7 );
                cerr << section << " : ";
                read_options( opts, config_file );
                bstring *d = opts.find_value( "Description" );
                cerr.width( 29 );
                cerr << ( ( d && *d != "" ) ? (const char *) *d : "Undefined" ) ;
                opts.erase_values();
                break;
        }
    }
}

//
// int read_ini_file( options &opts )
//
// ARGUMENTS:
//
//  opts      :  A reference to the options parameter that is used
//               throughout the program.  The options stucture has
//               a linked list of elements, each of which a tag
//               name and a value.  This routine reads those elemeents
//               out of BUILD.INI.
// RETURNS
//
//  1 if it is okay to keep going, 0 if a crummy command line got passed.
//
// DESCRIPTION
//
//  This routine opens up BUILD.INI, then scans until it finds a section
//  with the same name as the memory model specified on the command line.
//  If it doesn't find that section, it is considered an error, and a 0
//  is immediately returned to main().
//
//  If the correction section is found, read_options() is then called to
//  read all of the options into the options array.
//
//  After the first round of read_options(), we may have picked up the
//  names of some templates.  So we then go through a second round. For
//  each template that was defined in round 1, I search the file, find
//  the section, and read in some more options.  This continues until
//  all templates have been exhausted.  Just as a warning, nested
//  template definitions won't work.  The parsing mechanism ensures that
//  even if you modify the value of the Templates identifier, I won't
//  see the update in the polling loop.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A   : First release
//
//   January 5, 1995 3.0A : Updated to support templates

int read_ini_file( options &opts )
{
    bstring section;

#ifdef __SC__  // Symantec doesn't define binary, don't know how they do it, don't care
    fstream config_file( opts.ini_file, ios::in );
#else
    fstream config_file( opts.ini_file, ios::in | ios::binary );
#endif
    if ( config_file.fail() ) {
        cerr << "\nError - Could not open "
             << opts.ini_file
             << "!\n";
        return 0;
    }
    for ( ; ; ) {
        if ( get_next_section( section, config_file ) == NONE ) {
            cerr << "\nError - Couldn't find the section for model "
                 << opts.model
                 << " in "
                 << opts.ini_file
                 << "!\n";
            return 0;
        } else if ( section == opts.model )
            break;
    }
//
// This is where I read in the initial set of options
//
    if ( !read_options( opts, config_file ) )
        return 0;
//
// Here is where I ask the question: Does this section use
// any templates?
//
    bstring *templ = opts.find_value( "Template" );
    if ( templ == 0 )
        return 0;
//
// Now I have to read in a new section for each and every template I
// found.
//
    bstring templ_name = templ->get_first_token( "^" );
    while ( templ_name != "" ) {
        config_file.rdbuf()->seekoff( 0, ios::beg, ios::in );
        for ( ; ; ) {
            if ( get_next_section( section, config_file ) == NONE ) {
                cerr << "\nError - Couldn't find the template "
                     << templ_name
                     << " for model "
                     << opts.model
                     << " in "
                     << opts.ini_file
                     << "!\n";
                return 0;
            } else if ( section == templ_name ) {
                if ( read_options( opts, config_file ) == 0 )
                    return 0;
                else
                    break;
            }
        }
        templ_name = templ->get_next_token( "^" );
    }
    return 1;
}

//
// SECTION_TYPE get_next_section( bstring &section, fstream &file )
//
//
// ARGUMENTS:
//
//  section    :  The string where we return the name of the next section
//                after discovering it.
//
//  file       :  A reference to the open fstream object.
//
// RETURNS
//
//  Returns a SECTION_TYPE enum: NONE, HIDDEN, or NORMAL, depending
//  on what type of section we found.  Note that a section becomes
//  a hidden section if the first character of its name is ".".  If
//  that is the case, we strip the leading period here, so it looks
//  to the rest of the world as if it has a normal name.  In other words,
//  when I read in section [.DOS], I return HIDDEN, but switch the
//  name to DOS.  (The brackets get stripped too!)
//
// DESCRIPTION
//
//  This utility function is used by read_ini_file() and dump_sections().
//  All it does is advance through the file until it reaches the next
//  section.  A section in BUILD.INI is defined as a line that contains
//  nothing except "[string]".
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A   : First release
//
//   January 5, 1995 3.0A : Added support for hidden sections
//

SECTION_TYPE get_next_section( bstring &section, fstream &file )
{
    char buffer[ 129 ];
    for ( ; ; ) {
        file.getline( buffer, 129 );
        if ( file.fail() || file.eof() ) {
            section = "";
            file.clear( 0 );
            return NONE;
        }
        section = buffer;
//
// I had to open this file in binary mode because of some problems
// with Microsoft C++.  Since it is in binary mode, I get an extra '\r'
// which needs to be nuked.
//
        int index = section.first( '\r' );
        if ( index >= 0 && index == ( section.length() - 1 ) )
            section.remove_after( index - 1 );
        if ( section.first( '[' ) != 0 )
            continue;
        if ( section.last( ']' ) != ( section.length() - 1 ) )
            continue;
        section.remove_before( 1 );
        section.remove_after( section.length() - 2 );
//
// Detect and mung a hidden section
//
        if ( section[ 0 ] == '.' ) {
            section.remove_before( 1 );
            return HIDDEN;
        }
        return NORMAL;
    }
}

//
// int read_options( options &opts, fstream &file )
//
// ARGUMENTS:
//
//  opts      :  A reference to the options parameter that is used
//               throughout the program.  The options stucture has
//               a linked list of elements, each of which a tag
//               name and a value.  This routine reads those elements
//               out of BUILD.INI.
//
//  file      :  A reference to an open fstream connected to BUILD.INI.
//               This routine is called by read_ini_file(), and it is
//               that functions job to make sure that the input pointer
//               is sitting just at the right spot.  In this case the
//               spot should be right at the start of the first line 
//               of text immediately following the desired section.
// RETURNS
//
//  1 if it is okay to keep going, 0 if a crummy command line got passed.
//
// DESCRIPTION
//
//  This function is called by read_ini_file() during the startup of 
//  BUILD.  Its job is read in all of the options defined for the current
//  section.  It doesn't attempt to find the correct section, that
//  has to be done by read_ini_file() before this guy gets called.
//
//  This function is actually a little lazy also.  It reads in lines
//  from the INI file, checks to make sure they aren't comments or the
//  start of a new section, then calls parse_option() to do the
//  real work.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A   : First release
//
//   January 5, 1995 3.0A : Unchanged in this release.  Normally this would
//                          pass without comment, but so much other stuff
//                          changed that I thought I should mention it.
//

int read_options( options &opts, fstream &file )
{
    bstring line;
    char buffer[ 257 ];
//
// There is one little tricky bit here.  Before I read each line in, I
// mark the spot where the input buffer is currently sitting.  If the
// line i read in turns out to be the start of a new section, I back
// up the input pointer so that the next guy to read anything out of
// the INI file will start at that section.
//
    for ( ; ; ) {
        long spot = file.tellg();
        file.getline( buffer, 257 );
        if ( file.fail() || file.eof() ) {
            file.clear();
            return 1;
        }
        line = buffer;
//
// I had to open this file in binary mode because of some problems
// with Microsoft C++.  Since it is in binary mode, I get an extra '\r'
// at the end of the line which needs to be nuked.
//
        int index = line.first( '\r' );
        if ( index >= 0 && index == ( line.length() - 1 ) )
            line.remove_after( index - 1 );
//
// If this is the start of a new section, I have read in all the
// options I am going to get, so I can quit.
//
        if ( line[ 0 ] == '[' ) {
            file.rdbuf()->seekoff( spot, ios::beg, ios::in );
            return 1;
        }
// A comment or a blank line?
        if ( line[ 0 ] == ';' || line[ 0 ] == '\0' )
            continue;
// This line looks good, I call somebody else to do the parsing.
        if ( parse_option( opts, line ) == 0 )
            return 0;
    }
}

//
// int parse_option( options &opts, bstring &line )
//
// ARGUMENTS:
//
//  opts      :  A reference to the options parameter that is used
//               throughout the program.  The options stucture has
//               a linked list of elements, each of which a tag
//               name and a value.  This routine sets up one of those
//               elements based on what it finds in the command line
//               passed to it by read_options().
//
//  line      :  An actual line of input that has been read in from the
//               INI file.  It better be of the form "tag=value", or this
//               routine is going to complain and return an error.
//
// RETURNS
//
//  0 if the input line looked bad, 1 if it looked okay.  Note that if
//  this guy doesn't like an input line, it will return a value of
//  0, and the whole process will shut down.
//
// DESCRIPTION
//
//  This routine is a specialist at one thing only.  It takes a line that
//  somebody else took the trouble of reading in from the INI file, and
//  divides it into a tag and value.  It then inserts that tag and value
//  into the opts structure, so that anyone who wants to can take a gander
//  at it later in the program.
//
//  This function makes use of many member functions from the bstring
//  and options classes to do its work.  If they look a little strange,
//  you can view the class descriptions in BUILD.H.
//
//  In release 2.0B, I added support for multiple lines in a single command.
//  This was done to give me more control over the Link/Implib process
//  in CommLib.  You put multiple commands together on one line, separated
//  by a single caret ('^').  In this release, some of my Demo lines
//  were getting really long, and unreadable.  So in this release, I added
//  a new way to enter multiple lines.  You can now include multiple
//  lines with the same value in a section.  As each new value is encountered,
//  it gets appended to the existing value, with a caret to separate them.
//  Now multiple lines appear in the order to are going to execute them.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A    : First release
//
//   January 5, 1995  3.0A : New release supports multiple lines per command.
//

int parse_option( options &opts, bstring &line )
{
    bstring tag;

    int divide = line.first( '=' );  // Find the separator between tag and value
    if ( divide <= 0 ) {
        cerr << "\nError - Badly formed option line in "
             << opts.ini_file
             << ": "
             << line
             << "\n";
        return 0;
    }
    tag = line;
    tag.remove_after( divide - 1 );
    bstring *value = opts.find_value( tag );
    if ( value == 0 ) {
        cerr << "\nError - Unknown option found in "
             << opts.ini_file
             << ": "
             << line
             << "\n";
        return 0;
    }
//
// Note that this mangles the line, so the caller can't use it any more.
//
    line.remove_before( divide + 1 );
//
// If I already have this description on file, I am going to append it
// to the existing line.  I use the "^" symbol to separate lines
//
    if ( *value != "" )
        *value = *value + "^" + line;
    else
        *value = line;
    return 1;
}

//
// int build_file_list( int argc,
//                      char **argv,
//                      file_list &files,
//                      options& opts )
//
//
// ARGUMENTS:
//
//  argc      :  A count of the arguments left after the command
//               line has been partially parsed.
//
//  argv      :  A pointer to the array of strings that are the
//               arguments passed on the command line.
//
//  files     :  This is a reference to the structure that contains
//               the list of files that are going to be compiled.
//
//  opts      :  A reference to the options structure for this build.
//               By the time this function gets called, the entire
//               option list will have been filed out.  I need to know
//               about it here because it contains the directory list.
//
// RETURNS
//
//  0 if no files were added to the file list.  1 if some were.  main()
//  considers a value of 0 to be a good reason to abort.
//
// DESCRIPTION
//
//  This routine is called by main() after it has finished parsing the
//  INI file.  Its job is to go through the list of files on the command
//  line and add them all to the file list object.  It does this by
//  taking each of the file name arguments (which may or may not contains
//  wildcards), and checking each of the defined directories for the
//  presence of files that match the spec.  The actual expansion of the
//  wildcard and its addition to the file list is accomplished in 
//  add_wild_cards().
//
//  Note that if the user doesn't specify *any* file names on the command
//  line, we go ahead and parse "*.CPP", "*.C", and "*.ASM".  This is so
//  the build program can be run with even less thinking than before.
//
//  REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int build_file_list( int argc, char **argv, file_list &files, options& opts )
{
    char *default_files[ 10 ];
    bstring default_directories( "ALL" );
    bstring *dirs = opts.find_value( "Directories" );
    if ( dirs == 0 )
        dirs = &default_directories;
    if ( argc == 0 ) {
        bstring *s;
        s = opts.find_value( "Cpp" );
        if ( s != 0 && strlen( *s ) > 0 )
            default_files[ argc++ ] = "*.CPP";
        s = opts.find_value( "C" );
        if ( s != 0 && strlen( *s ) > 0 )
            default_files[ argc++ ] = "*.C";
        s = opts.find_value( "Asm" );
        if ( s != 0 && strlen( *s ) > 0 )
            default_files[ argc++ ] = "*.ASM";
        argv = default_files;
    }
//
// This loop is where I expand wildcards for each of the specified files,
// in each of the specified directories.
//
    for ( int i = 0 ; argc ; i++ ) {
        bstring ext = bstring( *argv ).ext();
        ext.remove_before( 1 );
        bstring search_dirs = *dirs;
        bstring dir;
        for ( dir = search_dirs.get_first_token();
              dir != "";
              dir = search_dirs.get_next_token() ) {
//
// Microsoft 8.0 chokes on this constructor, had to replace it with the
// alternate one below it.
//
//          bstring wild_guy( bstring( ROOT_DIR ) + ext + "_" + dir + "\\" + *argv );
            bstring wild_guy = bstring( ROOT_DIR ) + ext + "_" + dir + "\\" + *argv;
            add_wild_cards( files, wild_guy );
        }
        argv++;
        argc--;
    }
    if ( files.get_first_file() == 0 ) {
        cerr << "\nError - No files found to build!\n";
        return 0;
    }
    return 1;
}

//
// int build_demo_file_list( int argc,
//                           char **argv,
//                           file_list &files )
//
// ARGUMENTS:
//
//  argc      :  A count of the arguments left after the command
//               line has been partially parsed.
//
//  argv      :  A pointer to the array of strings that are the
//               arguments passed on the command line.
//
//  files     :  This is a reference to the structure that contains
//               the list of files that are going to be compiled.
//
// RETURNS
//
//  0 if no files were added to the file list.  1 if some were.  main()
//  considers a value of 0 to be a good reason to abort.
//
// DESCRIPTION
//
//  In release 3.0, we added the ability to build demo programs.  When
//  building libraries, we have a function just like this that is used
//  to build a list of files.  Unfortunately, we have to have a specialized
//  version of this function for building demos, because we specify files
//  in a slightly different way.  When building libraries, we always
//  specify files without a path name, like "STORCMP.CPP", and let BUILD
//  figure out which directories to search.  With demos it is different,
//  because we give a full path name.  So I have to perform a simpler
//  version of the wild card expansion in this routine.
//
//  REVISION HISTORY
//
//   January 5, 1995  3.0A : First release
//

int build_demo_file_list( int argc, char **argv, file_list &files )
{
    if ( argc == 0 ) {
        cerr << "\nError - No files found to build!\n";
        return 0;
    }
//
// This loop is where I expand wildcards for each of the specified files.
//
    for ( int i = 0 ; argc ; i++ ) {
        bstring wild_guy = *argv;
        add_wild_cards( files, wild_guy );
        argv++;
        argc--;
    }
//
// After it is all done, I check to see if I really got any files.
//
    if ( files.get_first_file() == 0 ) {
        cerr << "\nError - No files found to build!\n";
        return 0;
    }
    return 1;
}

//
// void add_wild_cards( file_list &files, const bstring &wild_spec )
//
// ARGUMENTS:
//
//  files     :  A reference to a file list structure.  The file list
//               is simply a linked list of file names.  My job here
//               is to expand the wild card I get passed and add the
//               names to this guy.
//
//  wild_spec :  This is the wild card specification, although it is not
//               necessarily a wild card, it might just be a name.
//
// RETURNS
//
//  None.
//
// DESCRIPTION
//
//  The user passes a list of file names on the command line, after
//  the model.  The names can be things like *.CPP and BOB.C.  The
//  routine that builds this file list takes each of those names,
//  and prepends each of the directories to it.  Then it calls this
//  guy to expand the resulting wild card specification and add it to
//  the file list structure.  Adding to the structure is done via 
//  a nice simple member function.
//
//  So if the guy types BUILD S *.CPP, this function might get called
//  three times, with the names "..\CPP_ALL\*.CPP", "..\CPP_DOS\*.CPP"
//  and "..\CPP_FOO\*.CPP".  I could add anywhere from zero to a zillion
//  file names to the list as a result;
//
//  REVISION HISTORY
//
//   May 18, 1994  2.0A  : First release
//

void add_wild_cards( file_list &files, const bstring &wild_spec )
{
    struct find_t ffblk;
    unsigned int result;
//
// Because of the way DOS expands names I need to break out the
// drive and path separately.  So, if I am expanding C:\BOB\*.CPP,
// I want to keep a copy here of C:\BOB\.  Then, as I expand the
// *.CPP part, I pack the resuling 8.3 name to the drive and path
// and voila, I have a complete filespec.
//
    bstring drive_and_path = wild_spec.drive() + wild_spec.path();

// The funny cast of wild_spec is to accomodate Symantec C.  They
// foolishly use char * instead of const char * for this arg.

    result = _dos_findfirst( (char *) (const char *) wild_spec, 0, &ffblk );
    while ( result == 0 ) {
        bstring new_name = drive_and_path + ffblk.name;
        files.add_file( new_name );   //Handy member function of class file_list
        result = _dos_findnext( &ffblk );
    }
}

//
// void build_config_files( options &opts, file_list &files )
//
// ARGUMENTS:
//
//  opts      :  This structure contains all of the options that have
//               been read out of the INI file.  I need to look at these
//               options so I can figure out which CMD files need to be
//               built.
//
//  files     :  A list of all the files that are going to get compiled.
//               I need this list so that I can build LIB.CMD, the librarian
//               response file.  It differs from the other CMD files
//               because it contains a dynamic list of object files,
//               not a static list of options straight out of BUILD.INI.           
//
// RETURNS
//
//  None.
//
// DESCRIPTION
//
//  Sometimes compiler or link commands get too big for the command line.  
//  When this happens, we have to put options into a response file, and
//  execute something like this:  CC blah blah @CC.CMD file.c.
//
//  The stuff that goes into the CMD file is stored in BUILD.INI.  It
//  is always stored in a tag with a name like xxxxOptions.  This routine
//  finds every option tag whose name ends with Options.  It then dumps
//  the value of that tag into a file called xxxx.CMD.  The xxxx is made
//  from the first part of the name.  So, for example, the tag named
//  LinkerOptions will get dumped into LINKER.CMD.
//
//  This routine does the work needed to identify each CMD file that needs
//  to be created.  It then calls build_config_file()( to actually parse
//  the options and store them in the file.
//
//  This routine also builds the LIB.CMD file, which is a little different.
//  It has to have a list of all the objects that are going to be built
//  on this pass.  But we just call another function to do that as well.
//
//  REVISION HISTORY
//
//   May 18, 1994  2.0A  : First release
//

void build_config_files( options &opts, file_list &files )
{
    for ( item *option = opts.get_first_item();
          option != 0;
          option = option->get_next_item() ) {
        if ( option->name == "Demo" )
            continue;
        int index = option->name.first( "Options" );
        if ( index != -1 ) {
            bstring filename = option->name;
            filename.remove_after( index - 1 );
            filename = filename + ".CMD";
            build_config_file( opts, filename, "", option->name );
        }
    }
    build_lib_cmd( opts, files );
}

//
// void process( bstring &result,
//               const char *command_string,
//               const bstring &file_name,
//               options &opts )
//
//
// ARGUMENTS:
//
//  buffer         :  A pointer to the destination buffer.  We will be
//                    building a command that goes into this buffer.  No
//                    range checking on output, sorry!!!
//
//  command_string :  A pointer to the command string.  This is the string
//                    that was actually read out of the INI file.  If there
//                    were multiple commands in one line, this guy is just
//                    one of them that has been separated out.  This command
//                    line should be chock full of special two digit
//                    formatting codes like %f, %l, etc.
//
//  file+name      :  The name of the source file being affected by this
//                    command.  This argument is really only meaningful for
//                    compilation, the rest of the time it is blank.
//
//  opts            :  This structure contains all of the options that have
//                     been read out of the INI file.  I need to look at these
//                     because I need to get the option value for this particular
//                     CMD file out of this structure.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//   This routine takes a command line and processes it.  Processing means
//   that it takes all the special two digit formatting codes and
//   substitutes the appropriate values in the output string.  The command
//   is built up and stored in an output string.  The following formatting
//   codes are supported:
//
//            %s : The complete file name for the source module being
//                 compiled.  This is only meaningful when we are building
//                 a list of object names for the librarian, or when calling
//                 the compiler or assembler for a source module.
//
//            %p:  The drive and path name.  This is not guaranteed to have
//                 a drive, but it is guaranteed to end in a "\\".  If the
//                 full path name is blank, you get this: ".\\";
//
//            %n:  The name of the file only.  This means the path and
//                 extension have been stripped.
//
//            %m:  The model letter, in lower case.  What I am calling the
//                 model letter is really just the first letter for the
//                 library name.  By convention, that is the same as the
//                 memory model.
//
//            %M:  The model letter, in upper case.
//
//            %l:  The name of the model, e.g. "L", or "100D".
//
//            %c:  The current value of the environment variable COMSPEC.
//                 If COMSPEC isn't defined, we will use COMMAND.COM
//                 This is useful if you are trying to execute batch files.
//
//  REVISION HISTORY
//
//   January 5, 1995
//

void process( bstring &result,
              const char *command_string,
              const bstring &file_name,
              options &opts )
{
    const char *p;
    char _temp[ 129 ];
    char *buffer = _temp;
    bstring path = file_name.drive() + file_name.path();
    bstring name = file_name.name();

    while ( *command_string ) {
        if ( *command_string == '%' ) {
            command_string++;
            switch ( *command_string ) {
                case 's' :
                    for ( p = file_name ; *p != 0 ; )
                        *buffer++ = *p++;
                    break;
                case 'p' :
                    for ( p = path ; *p != 0 ; )
                        *buffer++ = *p++;
                    break;
                case 'n' :
                    for ( p = name ; *p != 0 ; )
                        *buffer++ = *p++;
                    break;
                case 'm' :
                    *buffer++ = tolower( opts.model[ 0 ] );
                    break;
                case 'M' :
                    *buffer++ = toupper( opts.model[ 0 ] );
                    break;
                case 'l' :
                    for ( p = opts.model ; *p != 0 ; )
                        *buffer++ = *p++;
                    break;
                case 'c' :
                    p = getenv( "COMSPEC" );
                    if ( !p )
                        p = "COMMAND.COM";
                    for ( ; *p != 0 ; )
                        *buffer++ = *p++;
                    break;
                default :
                    *buffer++ = *command_string;
                    break;
            }
            command_string++;
        } else
            *buffer++ = *command_string++;
    }
    *buffer = '\0';
    result = _temp;
}

//
// int build_config_file( options &opts,
//                        const char *config_filename,
//                        const char *subject_filename,
//                        const bstring option_tag )
//
//
// ARGUMENTS:
//
//  opts       :  This structure contains all of the options that have
//                been read out of the INI file.  I need to look at these
//                because I need to get the option value for this particular 
//                CMD file out of this structure.
//
//  filename   :  The name of the CMD file that is going to be created.  
//                This name got figured out by build_config_files(), but     
//                he didn't bother to create it, so I still have to do
//                that.
//
//  option_tag :  This is the tag that will contain all of the stuff that
//                is supposed to go in the CMD file.  For example, if I
//                am building LINKER.CMD, this value would be "LinkerOptions".
//
// RETURNS
//
//  0 if I failed to build the file, 1 if things went well.
//
// DESCRIPTION
//
//  The CMD file is just a bunch of options that are written out
//  to a file.  I get the tag value from the options object, then
//  parse it into tokens.  Each token goes into a line of its own.
//
//  REVISION HISTORY
//
//   May 18, 1994  2.0A    : First release
//
//   January 5, 1995  3.0A :  Modified the routine so that it calls
//                            process() whenever it has a new line.
//                            This means you can perform substitution
//                            on any lines that are going to go into a
//                            config file.
//

int build_config_file( options &opts,
                       const char *config_filename,
                       const char *subject_filename,
                       const bstring option_tag )
{
    bstring *options = opts.find_value( option_tag );
    if ( options == 0 || options->length() == 0 )
        return 0;
//
// I like what I saw, so I open the config file for output
//
    fstream config_file( config_filename, ios::out );

    for ( bstring token = options->get_first_token() ;
          token.length() != 0;
          token = options->get_next_token() ) {
        bstring buf;
        process( buf, token, subject_filename, opts );
        config_file << buf << "\n";
    }
    return 1;
}

//
// int build_lib_cmd( options &opts, file_list &files )
//
//
// ARGUMENTS:
//
//  opts       :  This structure contains all of the options that have
//                been read out of the INI file.  I need to look at this
//                so I can get the value of "LibrarianFormat".
//                
//  files      :  This is a list of files that are going to be compiled 
//                during the build process.  Presumably each of these      
//                creates an OBJ file that needs to get added to the
//                the library.
//
// RETURNS
//
//  0 if I failed to build the file, 1 if things went well.
//
// DESCRIPTION
//
//  LIB.CMD has a slightly different format than  the other CMD files.
//  Instead of just putting a bunch of static junk into a CMD file,
//  we have to store the names of object files, using the LibrarianFormat
//  tag value as a template.  This means I have to walk through the list
//  of files, figure out the name of each object, then write it out.
//
//  There is also a little bit of a kludge here.  Almost all of the
//  librarians expect to see a "&" at the end of the line as a continuation.
//  They also will all be upset if you put the "&" at the end of a line
//  and then don't have another object afterwards.  So this routine puts
//  the ampersand into the print format as long as there are more files
//  left to go.  What a hack!
//
//  If any librarian ever comes along that wants a different continuation
//  character, we will have to add a new tag value to the build, probably
//  call LibrarianContinuationChar, or something like that.
//
//  REVISION HISTORY
//
//   May 18, 1994  2.0A  : First release
//
//   January 5, 1995  3.0A :  Modified the routine so that it calls
//                            process() whenever it has a new line.
//                            This means you can perform substitution
//                            on any lines that are going to go into a
//                            config file.

int build_lib_cmd( options &opts, file_list &files )
{
    fstream cmd_file( "LIB.CMD", ios::out );
    bstring *lib_cmd_fmt = opts.find_value( "LibrarianFormat" );
    bstring *file = files.get_first_file();
    while ( file ) {
        bstring buffer;
        process( buffer, *lib_cmd_fmt, file->name(), opts );
        file = files.get_next_file();
        if ( file == 0 || *file == "" )
            if ( buffer[ buffer.length() - 1 ] == '&'  )
                buffer.remove_after( buffer.length() - 2 );
        cmd_file << buffer;
        cmd_file << "\n";
    }
    return 1;
}

//
// void dump_options( options &opts )
//
//
// ARGUMENTS:
//
//  opts       :  This structure contains all of the options that have
//                been read out of the INI file.  They are what gets
//                printed out in this routine.
// RETURNS
//
//  None.
//
// DESCRIPTION
//
//  This routine is called by main() to display all of the current options
//  to the user before starting to compile.  All of the options are stored
//  in the opts array, and I just print them one at a time.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A    : First release
//
//   January 5, 1995  3.0A : Modified the code so that I don't spill
//                           over the end of the line if an option line
//                           is really long.  Instead, I just print some
//                           dots at the end of the line.
//

void dump_options( options &opts )
{
    cout.setf( ios::left );
//
// Symantec C++ does really funny things if you don't clear ios::right
//
    cout.unsetf( ios::right );
    cout.width( 15 );
    cout << "Model" << " : " << opts.model << "\n";
    for ( item *citem = opts.get_first_item() ;
          citem != 0;
          citem = citem->get_next_item() ){
        bstring token = citem->value.get_first_token( "^" );
        int i = 0;
        while ( token != "" ) {
            cout.width( 15 );
            if ( i++ == 0 )
                cout << citem->name;
            else
                cout << "";
            cout << " : ";
            if ( strlen( token ) > 59 ) {
                token.remove_after( 57 );
                token = token + "...";
            }
            cout << token << "\n";
            token = citem->value.get_next_token( "^" );
        }
    }
    cout << "\n";
}

//
// int compile_files( options &opts, file_list &files )
//
//
// ARGUMENTS:
//
//  opts       :  This structure contains all of the options that have
//                been read out of the INI file.  I need them here to
//                figure out how to compile each file.
//
//  files      :  The massive list of files.
//
// RETURNS
//
//  0 if any error occurs when compiling, 1 if every single file compiled
//  without error.
//
// DESCRIPTION
//
//  This routine is called by main() to compile all the files in the file
//  list.  The term "compiler" is used kind of loosely, because we don't
//  really care whether it is a compiler, assembler or what.
//
//  The way it works is that we step through the file list, processing files
//  one at a time.  Each file has a compile command, which is in the tag
//  specified by the file extension.  So, for example, if I want to compile
//  ..\CPP_ALL\KERMIT.CPP, I look up the tag CPP, and execute the command
//  stored there.  There are a few helper functions that help me accomplish
//  this.  One of the most important ones is execute(), because it has to
//  break the command down into tokens and stuff them into an argv[] array
//  before callling spawnv().  Another one is look_up_exec_file(), because
//  it has to search the path for the executable associated with a given
//  command.  For example, if the compile command is "bcc -c %s", we have
//  to look around until we find C:\BORLANDC\BCC.EXE, because that is
//  what spawnv() needs.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A    : First release
//
//   January 5, 1995  3.0A : Added the call to process() to provide complete
//                           substitution for formatting commands.  I used
//                           to use sprintf() with the file name, so that
//                           limited the substitutions.  Now a compiler line
//                           can include anything!
//

int compile_files( options &opts, file_list &files )
{
//
// I iterate through the loop, once per file name.  Note that the first
// thing I do is check to see if the object file exists.  If it does, we
// skip the compile step.  This is kind of dangerous, because we might have
// an object left over from a different memory model, but it saves a lot of
// time when building is interrupted by an error.
//
    bstring *file = files.get_first_file();
    while ( file ) {
        if ( object_file_exists( *file ) ) {
            cerr << "Skipping " << *file << "\n";
        } else {
//
// Once I have the file, I loop up the compile string, and the exec file.
// I use sprintf() to format a command line, then call the execute routine
// to make it all happen.
//
            bstring extension = file->ext();
            extension.remove_before( 1 );
            bstring *compile_string = opts.find_value( extension );
            bstring *exec_file = opts.look_up_exec_file( extension );
            if ( compile_string == 0 || exec_file == 0 ) {
                cerr << "Error compiling " << *file << ".  No compile command defined.\n";
                return 0;
            }
            bstring buffer;
            process( buffer, *compile_string, *file, opts );
            if ( execute( *exec_file, bstring( buffer ), opts.dry_run ) != 0 )
                return 0;
        } // object_exists
        file = files.get_next_file();
    }
    return 1;
}

//
// int compile_demo_files( options &opts, file_list &files )
//
//
// ARGUMENTS:
//
//  opts       :  This structure contains all of the options that have
//                been read out of the INI file.  I need them here to
//                figure out how to compile each file.
//
//  files      :  The massive list of files.
//
// RETURNS
//
//  0 if any error occurs when compiling, 1 if every single file compiled
//  without error.
//
// DESCRIPTION
//
//  This is the routine I call when the program is in demo building mode.
//  It is similar to the previous version used to compiler programs, but
//  has enough differences to justify a separate routine.  The first big
//  difference is that this guy will handle compound statements.  I can
//  use four or five different lines to build a demo.  Second, in the
//  previous function, I picked a command based on the extension of the
//  file.  In this routine, I only use the Demo command.  I think
//  that covers it.
//
// REVISION HISTORY
//
//   January 5, 1995  3.0A : First release.
//
//   January 5, 1995  3.0A : Added the call to process() to provide complete
//                           substitution for formatting commands.  I used
//                           to use sprintf() with the file name, so that
//                           limited the substitutions.  Now a compiler line
//                           can include anything!
//

int compile_demo_files( options &opts, file_list &files )
{
    bstring *compile_string = opts.find_value( "Demo" );
    if ( compile_string == 0 || *compile_string == "" ) {
        cerr << "Error in build of demo.  No compile command defined.\n";
        return 0;
    }

    bstring *file = files.get_first_file();
    while ( file ) {
        bstring command_string;
        command_string = compile_string->get_first_token( "^" );
        build_config_file( opts, "DEMO.CMD", *file, "DemoOptions" );
        while ( command_string != "" ) {
            bstring buffer;
            process( buffer, command_string, *file, opts );
            bstring exec_file;
            exec_file = find_executable( buffer.get_first_token() );
            if ( exec_file == "" ) {
                cerr << "Error compiling "
                     << *file
                     << ".  Can't find executable: "
                     << command_string.get_first_token()
                     << ".\n";
                return 0;
            }
            if ( execute( exec_file, bstring( buffer ), opts.dry_run ) != 0 )
                return 0;
            command_string = compile_string->get_next_token( "^" );
        }
        file = files.get_next_file();
    }
    return 1;
}

//
// int object_file_exists( const bstring &file )
//
//
// ARGUMENTS:
//
//  file        :  The name of a source file.  This can contain a full
//                 pathname and an extension.  Normally, this parameter
//                 will be something akin to "..\\CPP_WIN\FOO.ASM".
//
// RETURNS
//
//  1 if an object file exists, 0 if not.
//
// DESCRIPTION
//
//  This routine is called by compile_files().  It doesn't want to
//  compile a file if a good object for that file already exists.  
//  This routine just strips the path and extension, then checks to see if
//  an OBJ file exists in the current directory.  If so, it returns
//  a 1.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int object_file_exists( const bstring &file )
{
    FILE *p = fopen ( file.name() + ".OBJ", "r" );
    if ( !p )
        return 0;
    fclose( p );
    return 1;
}

//
// int execute( bstring &executable, bstring &command, int dry_run )
//
//
// ARGUMENTS:
//
//  executable :  This string containing the name of the executable.  If
//                the command line says that I am supposed to be executing
//                "bcc -I..\h filename", then the executable name needs to
//                be "c:\\borlandc\\bin\\bcc.exe", because the spawnv()
//                call doesn't search paths for you.
//
//  command    :  This is the command string, just as you would type it at
//                the DOS prompt, e.g. "cl /I..\H /AL /c foo.cpp".
//
//  dry_run    :  If this flag is set, it means the user has passed the
//                -cmd on the command line, meaning I don't really want
//                to execute the command, instead I just want to display
//                the commands that would have been executed.
//
// RETURNS
//
//  The return code from the spawn() command.  If things went okay it
//  will be a 0.  If the command didn't run it will be 0xffff. If it
//  is greater than 0, we assume the application ran and returned some
//  sort of error code.  If the user hits the escape key I return 1.
//
// DESCRIPTION
//
//  This is the function that actually executes a command.  We need a
//  completely separate function because of the way the spawn() functoin
//  works.  Instead of passing spawnv() a nicely built command line, we
//  have to break it apart into tokens, and pass an array of pointers
//  to those tokens.  What a pain!  Not only that, the tokens have to
//  be nice little char * objects, which means I have to allocate them
//  and then free them up after the command.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A   : First release
//
//   June 29, 1994 2.1A   : Added the ability to cancel by hitting the ESC key.
//
//   January 5, 1995 3.0A : Changed the token separator characters.  I was
//                          having a little problem with TLINK from Borland.
//                          it seems to want *all* of its arguments piled
//                          up in a single character.  When I separated them
//                          base on the comma character, I was getting lots
//                          of problems.  So, comma is no longer a separator.
//
int execute( bstring &executable, bstring &command, int dry_run )
{
    char *args[ 20 ];

    int i = 0;
    while ( kbhit() ) {
        int c = getch();
        if ( c == 0x1b ) {
            cerr << "User abort!\n";
            return 1;
        }
    }
    cerr << command << "\n";
    for ( bstring token = command.get_first_token( " " );
          token.length() != 0;
          token = command.get_next_token( " " ) ) {
        if ( i >= 22 ) {
            cerr << "\nError - Too many arguments in command!\n";
            return 1;
        }
        args[ i++ ] = strdup( token );
    }
    args[ i ] = strdup( "" );
    args[ i + 1 ] = 0;
    int ret_code = 0;
    if ( !dry_run ) {
#if defined( __TURBOC__ ) || defined( __WATCOMC__ )
        ret_code =  spawnv( P_WAIT, (char *)(const char *) executable, args );
#else
        ret_code =  spawnv( P_WAIT, (char *)(const char *) executable, (const char * const *) args );
#endif
        if ( ret_code != 0 ) {
            cerr << "Error code "
                 << ret_code
                 << " executing: <"
                 << command
                 << ">\n";
        }
    }
    for ( i = 0 ; i < 10 ; i++ )
        if ( args[ i ] == 0 )
            break;
        else
            free( args[ i ] );
    return ret_code;
}

//
// int build_library( options &opts )
//
//
// ARGUMENTS:
//
//  opts       :  The options object that contains all the tag settings
//                that were read out of BUILD.INI.  We need them because
//                they tell us how to run the librarian command.
//
// RETURNS
//
//  0 or 1, for failure or success.  Note that if I return a 0, BUILD
//  will exit with a failure.
//
// DESCRIPTION
//
//  This function is called to execute the librarian.  After all the files
//  have been compiled, it is easy to build the library.  All you have to
//  do is format and execute the librarian command, which is found under
//  tag "Librarian" in the options object.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A    : First release
//
//   January 5, 1995  3.0A : Added the call to process() so that we can
//                           do full formatting of the command line, even
//                           for the librarian.
//
int build_library( options &opts )
{
    bstring *lib_string = opts.find_value( "Librarian" );

    bstring buffer;
    process( buffer, *lib_string, "", opts );
    bstring exec_file;
    exec_file = find_executable( buffer.get_first_token() );
    if ( execute( exec_file, bstring( buffer ), opts.dry_run ) != 0 )
        return 0;
    return 1;
}

//
// int link_dll( options &opts )
//
//
// ARGUMENTS:
//
//  opts       :  The options object.  I need this because it holds
//                the linker command.
//
// RETURNS
//
//  0 if things didn't go well, otherwise a 1.
//
// DESCRIPTION
//
//  After building the library, we might need to create a DLL by
//  running the linker.  If so, this is where it gets done.  The
//  first thing it does is check to see if in fact there is a Linker
//  command defined.  If not, we can just return.  If there is a linker
//  command in the options object, we execute it, then the import
//  librarian.  If either of those return an error, we pass it back to
//  main().
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A    : First release
//
//   January 5, 1995  3.0A : Added the call to process(), so that linker
//                           command gets full format processing.
//

int link_dll( options &opts )
{
    bstring *linker_string = opts.find_value( "Linker" );
    if ( linker_string == 0 || *linker_string == "" )
        return 1;

    bstring command_string;
    command_string = linker_string->get_first_token( "^" );
    while ( command_string != "" ) {
        bstring buffer;
        process( buffer, command_string, "", opts );
        bstring exec_file;
        exec_file = find_executable( buffer.get_first_token() );
        if ( execute( exec_file, bstring( buffer ), opts.dry_run ) != 0 )
           return 0;
        command_string = linker_string->get_next_token( "^" );
    }
    return 1;
}

//
// int cleanup( file_list &files, options &opts )
//
//
// ARGUMENTS:
//
//  files      :  A list of the files that were processed.  This function
//                needs the list in order to delete all of the object
//                files.
//
// opts        :  The options object.  I need this because it contains
//                the DeleteFiles options, which tells me the names of
//                the other files to delete.
//
// RETURNS
//
//  Always returns a 1, indicating success.
//
// DESCRIPTION
//
//  This function is called by main() after all the steps in the build
//  have completed.  Its job is to delete all the objects that have been
//  left around, then any other files the BUILD.INI parameters may have
//  specified.  Deleting the objects is simply a matter of churning through
//  the list of files, deleting them one by one.  The list of files
//  to delete specified in DeleteFiles is pretty easy too, except I 
//  expand them first for wildcards.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int cleanup( file_list &files, options &opts )
{
//
// The first half of this routine is dedicated to deleting all
// the files specified in the DeleteFiles option of BUILD.INI
//
    bstring *delete_files = opts.find_value( "DeleteFiles" );
    if ( delete_files ) {
        for ( bstring wild_file = delete_files->get_first_token();
              wild_file != "";
              wild_file = delete_files->get_next_token() ) {
            struct find_t ffblk;
            unsigned int result;
//
// The funny cast of wild_spec is to accomodate Symantec C.  They
// foolishly use char * instead of const char * for this arg.
//
            result = _dos_findfirst( (char *) (const char *) wild_file, 0, &ffblk );
            while ( result == 0 ) {
                cerr << "DEL " << ffblk.name;
                if ( opts.keep_files )
                    cerr << "... Kept!";
                else
                    unlink( ffblk.name );
                cerr << "\n";
                result = _dos_findnext( &ffblk );
            }
        }
    }
//
// The second half of this routine is dedicated to deleting all of the
// objects left behind after the compile completed.
//
    bstring *file = files.get_first_file();
    while ( file ) {
        bstring obj_name = file->name() + ".OBJ";
        cerr << "DEL " << obj_name;
        if ( opts.keep_files )
            cerr << "... Kept!";
        else
            unlink( obj_name );
        cerr << "\n";
        file = files.get_next_file();
    }
    return 1;
}

//
// bstring find_executable( const bstring &s )
//
//
// ARGUMENTS:
//
//  s           :  The name of a command.  This normally won't have
//                 an extension, it will just be "cl", "bcc", or
//                 something like that.
//
// RETURNS
//
//  If we find an executable, we return a string containing the complete
//  path name.  If we don't find one, we just return an empty string.
//  The way this program works, I don't check the return, I just try
//  to execute the command.  I rely on the failure of the command
//  to figure out that something went wrong.
//
// DESCRIPTION
//
//  When it is time to spawn a command, I can't just pass "bcc" or "cl"
//  to the spawnv() function.  It needs a fully qualified path name,
//  and won't be happy unless it gets one.  This function is in charge
//  of searching through the dos PATH until it finds an executable file
//  with a given name.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//
//   NOTE****.  When I get around to it, I need to combine this function
//   and the other function that looks up executables.  One way might be
//   to start using spawnvp().  Another approach might be to cache file
//   names here, instead of in the opt structure.  In any case, I have
//   to call this function from compile_demo_files(), and I don't like
//   it.  The only routine that gets to use caching is compile_files(),
//   and that is only because it doesn't have to handle multiline
//   commands.
//

bstring find_executable( const bstring &s )
{
    bstring path = getenv( "PATH" );
    bstring dir;

    if ( exist( s ) )
        return s;
    for ( dir = path.get_first_token( ";" );
          dir != "";
          dir = path.get_next_token( ";" ) ) {
        if ( dir.index_from_end( 0 ) != '\\' )
            dir = dir + "\\";
        bstring filename = dir + s;
        if ( exist( filename ) )
            return filename;
        filename = dir + s + ".exe";
        if ( exist( filename ) )
            return filename;
        filename = dir + s + ".com";
        if ( exist( filename ) )
            return filename;
    }
    return "";
}

//
// int exist( const bstring &s )
//
//
// ARGUMENTS:
//
//  s        :  A file name.
//
// RETURNS
//
//  1 if the file exists, 0 if it does not.
//
// DESCRIPTION
//
//  find_executable() calls this guy to see if a file exists.  I used
//  to use the access() function, but it has trouble sometimes detecting
//  existence across a network.  This function works pretty reliably.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int exist( const bstring &s )
{
    FILE *f = fopen( s, "rb" );
    if ( f ) {
        fclose( f );
        return 1;
    }
    return 0;
}

//
// bstring::bstring( const char *init = "" )
//
//
// ARGUMENTS:
//
//  init        :  The character string to initialize the string to.
//
// RETURNS
//
//  No returns.
//
// DESCRIPTION
//
//  This is one of the constructors for my string class.  It initializes
//  the tokenizer pointer to 0 (since we don't need a tokenizer copy
//  until somebody calls get_first_token()).  It allocates space for
//  the initial string, then copies it.
//
//  Note that this guy generates an assertion error if the memory
//  allocation fails.  There should never be a time when a valid bstring
//  object has a null pointer in the string member.  Doing things this
//  way simplifies my life a little.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring::bstring( const char *init )
{
    if ( init == 0 )
        init = "";
    string = new char[ strlen( init ) + 1 ];
    assert( string );
    strcpy( string, init );
    tokenizer = 0;
}

//
// bstring::bstring( const bstring& rhs )
//
//
// ARGUMENTS:
//
//  rhs        :  The bstring object being used to construct this object.
//
// RETURNS
//
//  No returns from constructors.
//
// DESCRIPTION
//
//  This is one of the constructors for my string class.  It initializes
//  the tokenizer pointer to 0 (since we don't need a tokenizer copy
//  until somebody calls get_first_token()).  It allocates space for
//  the initial string, then copies it.
//
//  Note that this guy generates an assertion error if the memory
//  allocation fails.  There should never be a time when a valid bstring
//  object has a null pointer in the string member.  Doing things this
//  way simplifies my life a little.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring::bstring( const bstring& rhs )
{
    const char *p = rhs;
    string = new char[ strlen( p ) + 1 ];
    assert( string );
    strcpy( string, p );
    tokenizer = 0;
}

//
// bstring::~bstring()
//
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  None. 
//
// DESCRIPTION
//
//  The string destructor just has to free memory.  There will always
//  be memory allocated for the "string" member.  There may or may not
//  be memory allocated in the tokenizer member.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring::~bstring()
{
    delete[] string;
    if ( tokenizer )
        delete[] tokenizer;
}

//
// bstring& bstring::operator = ( const bstring& rhs )
//
//
// ARGUMENTS:
//
//  rhs        :  Another string object that is going to be copied into this.
//
// RETURNS
//
//  A reference to this.
//
// DESCRIPTION
//
//  This operator is used to copy one bstring object to another.  Note
//  once again the assertion error that occurs in the event of an
//  allocation failure.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring& bstring::operator = ( const bstring& rhs )
{
    if ( (const char *) rhs == string )
        return *this;
    delete[] string;
    string = new char[ strlen( rhs ) + 1 ];
    assert( string );
    strcpy( string, rhs );
    return *this;
}

//
// bstring& bstring::operator = ( const char *s )
//
// ARGUMENTS:
//
//  s          :  The character string to copy into this.
//
// RETURNS
//
//  A reference to this.
//
// DESCRIPTION
//
//  This copies a character string into a bstring.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring& bstring::operator = ( const char *s )
{
    if ( string == s )
        return *this;
    delete[] string;
    string = new char[ strlen( s ) + 1 ];
    assert( string );
    strcpy( string, s );
    return *this;
}

//
// bstring& bstring::upper()
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  A reference to this.
//
// DESCRIPTION
//
//  Converts a string to all upper case.
//
// REVISION HISTORY
//
//   January 5, 1995  3.0A : First release.
//

bstring& bstring::upper()
{
    for ( int i = 0 ; string[ i ] ; i++ )
        string[ i ] = toupper( string[ i ] );
    return *this;
}

//
// bstring bstring::operator + ( const char *s )
//
//
// ARGUMENTS:
//
//  s          :  A pointer to a character string.
//
// RETURNS
//
//  A bstring that results from adding s to this.  "Add" means concatenate.
//
// DESCRIPTION
//
//  This operator adds a character string to a bstring, creating a
//  new bstring.  This is very useful in a program like this, where
//  we are adding strings together all the time.  Note the assertion
//  error that takes place if a memory allocation fails.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring bstring::operator + ( const char *s )
{
    assert( s );
    char *p = new char[ strlen( string ) + strlen( s ) + 1 ];
    assert( p );
    strcpy( p, string );
    strcat( p, s );
    bstring new_guy( p );
    delete[] p;
    return new_guy;
}

//
// bstring bstring::operator + ( const bstring &rhs )
//
//
// ARGUMENTS:
//
//  rhs        :  A bstring that is going to be added to this.
//
// RETURNS
//
//  A bstring that results from adding s to this. "Add" means concatenate.
//
// DESCRIPTION
//
//  This operator adds a bstring to a bstring, creating a
//  new bstring.  This is very useful in a program like this, where
//  we are adding strings together all the time.  Note the assertion
//  error that takes place if a memory allocation fails.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring bstring::operator + ( const bstring &rhs )
{
    char *p = new char[ strlen( string ) + strlen( rhs ) + 1 ];
    assert( p );
    strcpy( p, string );
    strcat( p, rhs );
    bstring new_guy( p );
    delete[] p;
    return new_guy;
}

//
// int bstring::operator != ( const char *s )
//
//
// ARGUMENTS:
//
//  s          :  Pointer to a character string.
//
// RETURNS
//
//  True or false.
//
// DESCRIPTION
//
//  This is a wonderful function that we use all the time.  It lets
//  us compare bstrings using the != operator.  One major deal to note
//  is that string comaprisons are case insensitive.  If you don't know
//  this things aren't going to work quite like you expect.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int bstring::operator != ( const char *s )
{
    return stricmp( string, s );
}

//
// int bstring::operator == ( const char *s )
//
//
// ARGUMENTS:
//
//  s          :  Pointer to a character string.
//
// RETURNS
//
//  True or false.
//
// DESCRIPTION
//
//  This is a another function that we use all the time.  It lets
//  us compare bstrings using the == operator.  One major deal to note
//  is that string comaprisons are case insensitive.  If you don't know
//  this things aren't going to work quite like you expect.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int bstring::operator == ( const char *s )
{
    return !stricmp( string, s );
}

//
// int bstring::operator == ( const bstring &rhs )
//
//
// ARGUMENTS:
//
//  rhs          :  Reference to the bstring argument being compared to this.
//
// RETURNS
//
//  True or false.
//
// DESCRIPTION
//
//  This is a another function that we use all the time.  It lets
//  us compare bstrings using the == operator.  One major deal to note
//  is that string comaprisons are case insensitive.  If you don't know
//  this things aren't going to work quite like you expect.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int bstring::operator == ( const bstring& rhs )
{
    return !stricmp( string, rhs );
}


//
// int bstring::first( char c )
//
//
// ARGUMENTS:
//
//  c        :  The character to search for.
//
// RETURNS
//
//  An index, ranging from 0 to ( strlen( this ) -1 ) if the character
//  is found, or -1 if it isn't found.
//
// DESCRIPTION
//
//  This function finds the first appearance of character c in bstring this.
//  It returns the index of the character.
//
// One really bad deal here is that this search *is* case sensitive, which
// really differs from the rest of the library.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int bstring::first( char c )
{
    char *p = strchr( string, c );
    if ( p == 0 )
        return -1;
    else
        return (int) ( p - string );
}

//
// int bstring::first( const char *s )
//
//
// ARGUMENTS:
//
//  s        :  The string to search for.
//
// RETURNS
//
//  An index, ranging from 0 to ( strlen( this ) -1 ) if the substring
//  is found, or -1 if it isn't found.
//
// DESCRIPTION
//
//  This function finds the first appearance of substring s in bstring this.
//  It returns the index of the first character of the substring.
//
// One really bad deal here is that this search *is* case sensitive, which
// really differs from the rest of the library.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int bstring::first( const char *s )
{
    char *p = strstr( string, s );
    if ( p == 0 )
        return -1;
    else
        return (int) ( p - string );
}

//
// int bstring::last( char c )
//
//
// ARGUMENTS:
//
//  c        :  The character to search for.
//
// RETURNS
//
//  An index, ranging from 0 to ( strlen( this ) -1 ) if the character
//  is found, or -1 if it isn't found.
//
// DESCRIPTION
//
//  This function finds the last appearance of character c in bstring this.
//  It returns the index of the character.
//
// One really bad deal here is that this search *is* case sensitive, which
// really differs from the rest of the library.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int bstring::last( char c )
{
    char *p = strrchr( string, c );
    if ( p == 0 )
        return -1;
    else
        return (int) ( p - string );
}

//
// int bstring::remove_after( int index )
//
//
// ARGUMENTS:
//
//  index      :  The point in the string which will now be the last
//                character.
//
// RETURNS
//
//  0 if the index is no good, otherwise 1.
//
// DESCRIPTION
//
//  This function lets you chop off the end of a bstring.  It deletes
//  everything after a specific index.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int bstring::remove_after( int index )
{
    if ( index >= (int) strlen( string ) )
        return 0;
    if ( index < -1 )
        return 0;
    string[ index + 1 ] = '\0';
    return 1;
}

//
// int bstring::remove_before( int index )
//
//
// ARGUMENTS:
//
//  index      :  The point in the string which will now be the first
//                character.
//
// RETURNS
//
//  0 if the index is no good, otherwise 1.
//
// DESCRIPTION
//
//  This function lets you chop off the start of a bstring.  It deletes
//  everything before a specific index.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int bstring::remove_before( int index )
{
    if ( index > (int) strlen( string ) )
        return 0;
    if ( index < 0 )
        return 0;
    char *dest = string;
    char *source = string + index;
    while ( ( *dest++ = *source++ ) != '\0' )
        ;
    return 1;
}

//
// int bstring::operator[]( int index ) const
//
//
// ARGUMENTS:
//
//  index    :  This indexing operator lets you safely get
//              a character out of a bstring.  You can pass a no
//              good index and this function will deal with it.
//
// RETURNS
//
//  The character, or a -1 if the index is no good.
//
// DESCRIPTION
//
//  This indexing operator returns a character from the bstring.  If
//  for some reason the index is no good, it returns a -1.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int bstring::operator[]( int index ) const
{
    if ( index < 0 )
        return 0;
    if ( index >= (int) strlen( string ) )
        return 0;
    return string[ index ];
}

//
// int bstring::index_from_end( int index ) const
//
//
// ARGUMENTS:
//
//  index      : The index into the string.
//
// RETURNS
//
//  Either the character from the string, or a -1 if the index is no good.
//
// DESCRIPTION
//
//  Sometimes I want to get a character that is a certain distance from the
//  end of the string.  This is just like the [] operator, except it 
//  operates in revers.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

int bstring::index_from_end( int index ) const
{
    index = strlen( string ) - index;
    if ( index < 0 )
        return 0;
    if ( index >= (int) strlen( string ) )
        return 0;
    return string[ index ];
}

//
// bstring bstring::drive() const
//
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  The drive component of a file name.  If the drive component
//  is not present in the file name, and empty string is returned.
//
// DESCRIPTION
//
//  This is one of four bstring functions that help to support 
//  separation of filenames into components.  If the filename has
//  a drive component, this guy will strip it out, put it in a 
//  new string, and return it.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring bstring::drive() const
{
    bstring drive_name = *this;
    if ( drive_name != "" ) {
        int i = drive_name.first( ':' );
        if ( i == -1 )
            drive_name = "";
        else
            drive_name.remove_after( i );
    }
    return drive_name;
}

//
// bstring bstring::path() const
//
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  The path component of a file name.  If the path component
//  is not present in the file name, we return sort of a default
//  path, "..\\";
//
// DESCRIPTION
//
//  This is one of four bstring functions that help to support
//  separation of filenames into components.  This function sort
//  of tries to second guess the best thing to return for the path
//  component of a file name.  I'm not sure this is as good as it
//  should be, but it works for BUILD.CPP.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring bstring::path() const
{
    bstring path = *this;
    int i = path.first( ':' );
    if ( i != -1 )
        path.remove_before( i + 1 );
//
// Now we might have :
//     \\comp1\\comp2\\name  which should return "\\comp1\\comp2\\"
//     name                  which should return ".\\"
//     \\name return         which should return "\\"
//     \\name\\              which should return "\\name""
//     comp1\\comp2\\name    which should return "comp1\\comp2\\"
//
    i = path.last( '\\' );
    if ( i != -1 ) {
        path.remove_after( i );
        if ( path.first( '\\' ) == 0 )
            path = bstring( ".\\" ) + path;
        return path;
    }
//
// Now we might have :
//     name                  which should return ".\\"
//
    return path = ".\\";
}

//
// bstring bstring::name() const
//
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  The name component of a file name.  Note that in an 8.3 system,
//  this function returns the 8, but no decimal point.  The point
//  gets returned with the extension.
//
// DESCRIPTION
//
//  This is one of four bstring functions that help to support
//  separation of filenames into components.  This function returns
//  the name portion of the file.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring bstring::name() const
{
    bstring name = *this;
    int i = name.last( '\\' );
    if ( i >= 0 )
        name.remove_before( i + 1 );
    else {
        i = name.first( ':' );
        if ( i >= 0 )
            name.remove_before( i + 1 );
    }
    i = name.first( '.' );
    if ( i >= 0 )
        name.remove_after( i - 1 );
    return name;
}

//
// bstring bstring::ext() const
//
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  The extension component of a file name.  Note that in an 8.3 system,
//  this function returns the 3 letter extension, along with the
//  decimal point.  A lot of times you will want to strip that
//  decimal point.  In fact, I think I just about always strip it.
//
// DESCRIPTION
//
//  This is one of four bstring functions that help to support 
//  separation of filenames into components.  This function returns
//  the extension portion of the file.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring bstring::ext() const
{
    bstring ext = *this;
    int i = ext.last( '.' );
    if ( i >= 0 )
        ext.remove_before( i );
    else
        ext = ".";
    return ext;
}

//
// bstring bstring::get_first_token( const char *s = ", " )
//
//
// ARGUMENTS:
//
//  s   : A string containing all the token delimiters.
//
// RETURNS
//
//  A string containing the first token from the string.  If there
//  is no token you get an empty string.
//
// DESCRIPTION
//
//  The get_first_token() / get_next_token() interface is really useful.
//  It lets you suck tokens out of a string, using an arbitrary set of
//  delimiters.  Usually we are just looking for tokens separated by
//  spaces, but when parsing the dos PATH, we look for tokens separated
//  by semicolons.
//
//  To make this work properly, the guy makes a little copy of the string,
//  and mangles it as we go along.  When we are done with it it gets
//  deleted.  It might be just as easy to just use a pointer into the
//  string, but this is what I ended up with.  It works.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring bstring::get_first_token( const char *s /* = " ," */ )
{
    if ( tokenizer )
        delete[] tokenizer;
    tokenizer = new char[ strlen( string ) + 1 ];
    assert( tokenizer );
    strcpy( tokenizer, string );
    return get_next_token(s );
}

//
// bstring bstring::get_next_token( const char *delimiters = " ," )
//
//
// ARGUMENTS:
//
//  s   : A string containing all the token delimiters.
//
// RETURNS
//
//  A string containing the next token from the string.  If there
//  is no token you get an empty string.
//
// DESCRIPTION
//
//  The get_first_token() / get_next_token() interface is really useful.
//  It lets you suck tokens out of a string, using an arbitrary set of
//  delimiters.  Usually we are just looking for tokens separated by
//  spaces, but when parsing the dos PATH, we look for tokens separated
//  by semicolons.
//
//  To make this work properly, the guy makes a little copy of the string,
//  and mangles it as we go along.  When we are done with it it gets
//  deleted.  It might be just as easy to just use a pointer into the
//  string, but this is what I ended up with.  It works.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring bstring::get_next_token( const char *delimiters /* = " ," */ )
{
    assert( tokenizer );
    char *temp_src = tokenizer + strspn( tokenizer, delimiters );
    for ( char *temp_dest = tokenizer ;
          *temp_src != '\0';
          *temp_dest++ = *temp_src++ )
        ;
    *temp_dest = '\0';
    if ( *tokenizer == '\0' ) {
        delete[] tokenizer;
        tokenizer = 0;
        return "";
    }
    temp_src = tokenizer + strcspn( tokenizer, delimiters );
    char temp = *temp_src;
    *temp_src = '\0';
    bstring result = tokenizer;
    *temp_src = temp;
    for ( temp_dest = tokenizer;
          *temp_src != '\0';
          *temp_dest++ = *temp_src++ )
        ;
    *temp_dest = '\0';
    return result;
}

//
// options::options( char *first, ... )
//
//
// ARGUMENTS:
//
//  first    : The name of the first option
//
//  ...      :  A list of character strings containing the names of
//              any other options we expect to find.  The list needs
//              to be terminated with a NULL pointer or an empty string.
//
// RETURNS
//
//  Constructor, no returns
//
// DESCRIPTION
//
//  The options class holds all the options we need to use in order
//  to build a library.  The bulk of the information in the options
//  structure consists of tag names and values that are read out of
//  BUILD.INI.  A line in BUILD.INI looks like this:
//
//      tag=value
//
//  This implementation of the options class inists that we define all
//  the tag names in advance, here in the constructor.  It would be
//  easy to change the class so that new names encountered in BUILD.INI
//  could be added dynamically, but I think it would then be harder to
//  track down typos in the INI file, don't you.
//
//  This constructor is in charge of setting up the tag items with blank
//  values.  When BUILD.EXE is busy processing the files, it will assigne
//  the values to each of the tags as it encounters them.
//
//  There are two additional data members in options that don't get set up
//  here (although they probably should).  One is the memory model read in
//  from the command line.  The other is the dry_run member, used to 
//  tell the program to go through the motions of building a library,
//  but not to really do it.
//
// REVISION HISTORY
//
//   May 20, 1994  2.0A  : First release
//

options::options( char *first, ... )
{
    va_list ap;
    char *arg;

    va_start( ap, first );
    first_item = 0;
    arg = first;
    while ( arg != 0 && strlen( arg ) > 0 ) {
        item *new_item = new item( arg );
        assert( new_item );
        new_item->next_item = first_item;
        first_item = new_item;
        arg = va_arg( ap, char * );
    }
}

//
// bstring *options::find_value( char const *tag )
//
//
// ARGUMENTS:
//
//  tag       :  The name of the tag whose value we want.
//
// RETURNS
//
//  A bstring pointer, which points to the actual tag in the list opt option
//  items.  If the tag could not be found, it returns a null pointer.
//
// DESCRIPTION
//
//  This is the function I use to look up a tag value.  It returns a bstring
//  directly, so it is really easy to use.  It might be even better to try
//  to overload the [] operator with a string, but I don't know if you can
//  actually do that.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring *options::find_value( char const *tag )
{
    item *current_item;
    for ( current_item = first_item ; ; current_item = current_item->next_item ) {
        if ( current_item == 0 )
            return 0;
        if ( current_item->name != "" && current_item->name == tag )
            return &current_item->value;
    }
}

//
// bstring *options::look_up_exec_file( char const *tag )
//
//
// ARGUMENTS:
//
//  tag       :  A string indicating which tag we are doing the lookup for.
//
// RETURNS
//
//  A pointer to a bstring, 0 if the tag is not found.
//
// DESCRIPTION
//
//  This is another very handy member function.  Many of the tags in 
//  the options object contain DOS commands that we will eventually
//  run using spawnv().  Whenenver it is time to run one of these commands,
//  like CL.EXE, we have to search the DOS path in order to find the
//  executable file, because spawnv() is too lazy to do the job itself.
//  We don't want to have to search for the executable every time we run
//  the program however.  
//
//  To solve this, we look up the executable only once, then store the
//  results in the exec_file bstring data member of the option item.
//  Next time the user calls us to find the executable, we have it
//  on hand and can return it without any fuss.
//
//  Note that I assume that the command I am looking up will be the very
//  first token in the command line.  Note also that I don't do the hard
//  job of searching the path, I leave that up to find_executable();
//
// REVISION HISTORY
//
//   May 20, 1994  2.0A  : First release
//

bstring *options::look_up_exec_file( char const *tag )
{
    item *current_item;
    for ( current_item = first_item ; ; 
          current_item = current_item->next_item ) {
        if ( current_item == 0 )
            return 0;
        if ( current_item->name != "" && current_item->name == tag ) {
//
// I have to execute this code to find the exec_file the first time through.
//
            if ( current_item->exec_file == "" ) {
                bstring program = current_item->value.get_first_token();
                current_item->exec_file = find_executable( program );
            }
            return &current_item->exec_file;
        }
    }
}

//
// void options::erase_values()
//
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  This function goes through the options list and sets each tag items'
//  value to the empty string.  I do this when I am scanning the INI
//  file in dump_sections().  Normally, when you read in an item for a
//  second time, you would generate an error.
//
// REVISION HISTORY
//
//   May 20, 1994  2.0A  : First release
//

void options::erase_values()
{
    item *current_item;
    for ( current_item = first_item ; ; current_item = current_item->next_item ) {
        if ( current_item == 0 )
            return;
        current_item->value = "";
    }
}

//
// bstring *file_list::get_first_file()
//
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  A pointer to a bstring.  When there are no more files to return,
//  we return a null pointer.
//
// DESCRIPTION
//
//  I keep all of the files I am going to compile in a file_list object.
//  When iterating through the list, I use the get_first_file() 
//  get_next_file() functions.  This is the get_first_file().  Note that
//  I keep track of where I am in the list using the internal protected
//  member current_item.  This value gets set up here for the first
//  time so that subsequent calls to get_next_file() will know where
//  to continue the search.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

bstring *file_list::get_first_file()
{
    current_item = first_file;
    if ( current_item )
        return &current_item->file_name;
    else
        return 0;
}

//
// bstring *file_list::get_next_file()
//
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  If another file is available in the list, we return a pointer to
//  it.  If we reached the end of the list, we return a null pointer.
//
// DESCRIPTION
//
//  This is the companion function to get_first_file().
//
// REVISION HISTORY
//
//   May 20, 1994  2.0A  : First release
//

bstring *file_list::get_next_file()
{
    if ( current_item )
        current_item = current_item->next_item;
    if ( current_item )
        return &current_item->file_name;
    else
        return 0;
}

//
// void file_list::add_file( const char *name )
//
//
// ARGUMENTS:
//
//  name   :  The name of the file to add to the list.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  During the startup of this program, we add files to the file list.
//  This is the function that does it.  It creates a new item, and
//  assigns it the appropriate name.  Note that any memory allocation
//  failure causes an assertion error and the whole deal goes to sleep.
//
//  If I had bothered to put an end_of_list pointer in the file_list
//  class, this function would be a lot more efficient, at a very small
//  price.  Oh well.
//
// REVISION HISTORY
//
//   May 19, 1994  2.0A  : First release
//

void file_list::add_file( const char *name )
{
//
// Let's add the new guy to the end of the list!
//
    file_name_item *new_guy = new file_name_item( name );
    assert( new_guy );
    file_name_item **list = &first_file;
    while ( *list != 0 )
        list = &(*list)->next_item;
    *list = new_guy;
    new_guy->next_item = 0;
}
