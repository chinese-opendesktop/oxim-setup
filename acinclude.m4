#######################################################################################
##
##   GB_FIND() macro is part of gambas2 project
##   by Benoit Minisini
##   others are from me (Laurent Carlier)
##
#######################################################################################

## ---------------------------------------------------------------------------
## GB_INIT_PROJECT
## Initialization and checking for gambas things
##
##   $1 = gambas2 project to build 
## ---------------------------------------------------------------------------

AC_DEFUN([GB_INIT_PROJECT],
[
  if !(test -e src/$1/.project); then
    AC_MSG_ERROR(Cannot find .project file for src/$1 !)
  fi

  ##AM_INIT_AUTOMAKE(src/$1, `cat src/$1/.project | grep "Version=" | sed s/"Version="//g`)
  AM_INIT_AUTOMAKE(src/$1, 0.1)

  ## List of needed components
  COMPONENTS=`cat src/$1/.project | grep "Library=" | sed s/"Library="//g`

  ## Check if the project is a component
  COMPONENT_build=`cat src/$1/.project | grep "MakeComponent=" | sed s/"MakeComponent="//g`
  AC_SUBST(COMPONENT_build)

  AC_MSG_CHECKING(for gambas2 binaries)
  GAMBAS_path=`gbx2 -e system.path`/bin
  if test "$?" != "0"; then
    AC_MSG_RESULT(No)
    AC_MSG_WARN(Failed to find gambas2 utilities, check your gambas2 installation !)
    enable_gb_enviorment="no"
  else
    AC_MSG_RESULT(Ok)
    AC_SUBST(GAMBAS_path)
    enable_gb_enviorment="yes"
  fi

  ## Find component components path
  AC_MSG_CHECKING(for gambas2 components path)
  GBLIBRARY_path=`gbx2 -e component.path`
  if test "$?" != "0"; then
    AC_MSG_RESULT(No)
    AC_MSG_WARN(Failed to find gambas2 library path !)
    enable_gb_enviorment="no"
  else
    AC_MSG_RESULT(Ok)
    AC_SUBST(GBLIBRARY_path)
    enable_gb_enviorment="yes"
  fi

  GBINFO_path=`echo $GBLIBRARY_path | sed s/"\/lib\/gambas2"/"\/share\/gambas2\/info"/`
  AC_SUBST(GBINFO_path)

  GBCONTROL_path=`echo $GBLIBRARY_path | sed s/"\/lib\/gambas2"/"\/share\/gambas2\/control"/`
  AC_SUBST(GBCONTROL_path)

  GBHOME_path=`gbx2 -e user.home`/.local/lib/gambas2

  for comp in $COMPONENTS; do
    if test "$comp" = "src/$1"; then continue; fi
    AC_MSG_CHECKING(for $comp component)
    GB_FIND(${comp}.component, $GBLIBRARY_path $GBHOME_path, ./)
    if test "$gb_val" = "no"; then
      AC_MSG_RESULT(No)
      AC_MSG_WARN(Failed to find $comp component !)
      enable_gb_enviorment="no"
    else
      AC_MSG_RESULT(Ok)
      enable_gb_enviorment="yes"
    fi
  done

  AM_CONDITIONAL(GB_READY, [ test "$enable_gb_enviorment" = "yes" ])
])

## ---------------------------------------------------------------------------
## GB_FIND
## Find files in directories
##
##   $1 = Files to search
##   $2 = Directories
##   $3 = Sub-directories patterns
##
##   Returns a path list in $gb_val
## ---------------------------------------------------------------------------

AC_DEFUN([GB_FIND],
[
dnl echo "Searching $1, $2, $3"
gb_val=""
gb_save=`pwd`
gb_file_list="$1"

for gb_main_dir in $2; do
  if test -d $gb_main_dir; then
    cd $gb_main_dir
    for gb_search_dir in $3; do
      for gb_dir in $gb_search_dir/ $gb_search_dir/*/ $gb_search_dir/*/*/; do

        gb_new_file_list=""
        gb_find_dir=""

        for gb_file in $gb_file_list; do

          gb_find=no
          if test -r "$gb_main_dir/$gb_dir/$gb_file" || test -d "$gb_main_dir/$gb_dir/$gb_file"; then

            ifelse($4,[],

              gb_find=yes,

              for gb_test in $4; do
                gb_output=`ls -la $gb_main_dir/$gb_dir/$gb_file | grep "$gb_test"`
                if test "x$gb_output" != "x"; then
                  gb_find=yes
                fi
              done
            )

          fi

          if test "$gb_find" = "yes"; then
            if test "x$gb_find_dir" = "x"; then
              if test "x$gb_val" = "x"; then
                gb_val="$gb_main_dir/$gb_dir"
              else
                gb_val="$gb_val $gb_main_dir/$gb_dir"
              fi
            fi
            gb_find_dir=yes
          else
            gb_new_file_list="$gb_new_file_list $gb_file"
          fi

        done

        gb_file_list=$gb_new_file_list

        if test "x$gb_file_list" = "x " || test "x$gb_file_list" = "x"; then
          break 3
        fi

      done
    done
  fi
done

if test "x$gb_file_list" != "x " && test "x$gb_file_list" != "x"; then
  gb_val=no
fi

cd $gb_save
])
