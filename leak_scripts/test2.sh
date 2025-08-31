#!/usr/bin/env bash
# =============================
# Stress com variáveis grandes
# =============================
export LONGVAR=$(printf 'x%.0s' {1..10000})
echo ${#LONGVAR}
unset LONGVAR

# =============================
# Expansão + Redirecionamento
# =============================
echo "$HOME" > /tmp/msh_out2 && cat < /tmp/msh_out2 && rm -f /tmp/msh_out2

# =============================
# Many pipes (profundidade > 10)
# =============================
echo a | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | wc -l

# =============================
# Heredoc edge cases
# =============================
cat <<EOF
EOF
cat <<STOP
STOP

# Delimitador vazio (não deve travar)
cat << ""

# =============================
# Comandos inválidos em pipe
# =============================
ls | naoexiste | wc -l

# =============================
# Redirecionamentos múltiplos
# =============================
echo a > f1 > f2 > f3
rm -f f1 f2 f3

# =============================
# Concorrência com sleep/exit
# =============================
sleep 0.1 | echo done
(exit 7) ; echo $?

# =============================
# Códigos de saída propagados
# =============================
false
echo $?
true
echo $?
ls inexistente 2>/dev/null
echo $?

# =============================
# Sequências de ; e &&, ||
# =============================
echo a ; echo b ; echo c
false && echo nao_deve
true && echo deve
false || echo deve
true || echo nao_deve

# =============================
# Aspas e escapes
# =============================
echo "\"aspas\" simples"
echo "linha1\
linha2"

# =============================
# Substituição complexa
# =============================
echo $HOME$PATH$USER
echo "$HOME$PATH$USER"

# =============================
# Stress loops com history
# =============================
echo test1
echo test2
echo test3
history | tail -n 3

EOF
