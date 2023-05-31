#!/bin/bash

# Utilização
# Executar este script
#
# Funcionalidade
# Compila o script em cpp
# Compara todos os casos de teste nas pastas testCases
# Cria o ficheiro *casoteste*.out_temp com resultado de correr cada caso de teste
#
# Flags
# -c apagar os ficheiros *casotest*.out_temp após correr cada caso de teste

# ANSI color codes for formatting
GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m' # No color

g++ -std=c++17 -Wall -Wextra -O2 -o e.out pyramidScheme.cpp -lm

TIMEFILE="timefile"

out=$(ls -v ./testCases/*.txt)
count=1
for ef in $out; do
   A="${ef//\.txt/.out_temp}"
   B="${ef//\.txt/.output}"
   /usr/bin/time -v -o "${TIMEFILE}" ./e.out < "$ef" > "$A"

   if diff -q "$A" "$B" >/dev/null; then
      echo -e "----------\n${GREEN}PASS TEST $count${NC}:\n $ef\n----------"
   else
      echo -e "----------\n${RED}FAIL TEST $count${NC}:\n $ef\n----------"      
   fi

   count=$((count+1))

   if [[ ! -z $1 && $1 = "-c" ]]; then
      rm -Rf "$A" "${TIMEFILE}"
   fi
done
