#!/usr/bin/env bash
# Colete/edite seus casos aqui. Cada linha é um comando a ser alimentado ao minishell.
# Linhas começando com # são ignoradas.

read -r -d '' CASES << 'EOF'
# Builtins básicos
echo hello
pwd
env
export
export A=1
export B="  two  "
export A=2 B=3
export EMPTY=
unset B
unset NOT_SET
echo $A $B $EMPTY$NOT_SET

# Expansões e aspas
echo "$A"
echo '$A'
echo "$A$B"
echo "$?"
echo $HOME
echo "$HOME"
echo ~
echo "~"
echo "a   b" | cat -e

# Comandos externos simples
/bin/echo ok
which ls
ls not_a_file 2>/dev/null

# Redirecionamentos
echo 42 > /tmp/minishell_test_file
cat < /tmp/minishell_test_file
rm -f /tmp/minishell_test_file
echo falha 1> /dev/null
echo erro 2> /dev/null
echo dup both > /tmp/msh_out 2>&1
rm -f /tmp/msh_out

# Pipes
echo ola | tr a-z A-Z
echo a b c | cat | wc -w
echo pipeerr | grep z | cat

# Vários pipes + redirects
echo a | cat | cat | grep a > /dev/null
echo a | cat | cat | grep b > /dev/null

# Heredoc (não-interativo)
cat << EOF
line1
line2
EOF
cat << STOP | wc -l
a
b
c
STOP

# Erros de sintaxe (devem falhar, mas sem leaks)
|
|||
<  >  |
cat < inexistente 2>/dev/null
> /root/deny 2>/dev/null

# Comandos que não existem
naoexiste
naoexiste | cat

# Muitas variáveis / stress leve
export X1=1 X2=2 X3=3 X4=4 X5=5 X6=6 X7=7 X8=8 X9=9 X10=10
unset X1 X2 X3 X4 X5 X6 X7 X8 X9 X10
EOF
