# string_sort

reads all lines from input file, sorts them and puts to standard output.

Command line arguments:
  - --file [filename]      : used to specify input file. Default name is "input.txt"
  - --invert-sorting       : inverts sorting order.
  - --rtl-sorting          : compares lines right-to-left instead of left-to-right. (makes last characters most significant in sorting)
  - --remove-leading-spaces: removes all leading spaces from lines.  
  - --shakespeare-mode     : removes lines NOT startig with ' '; removes all lines starting with "Enter", "Exit", "Re-enter" and "Exeunt"; Works best with --remove-leading-spaces; Was created to support format of "Hamlet"

Compilation: make all
  
  
