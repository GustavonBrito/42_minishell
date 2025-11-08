#!/usr/bin/env bash
# =======================================
# FILE DESCRIPTORS
# =======================================

# Pipe longo - deve fechar todos os FDs
echo fd1 | cat | cat | cat | cat | cat | cat | cat | cat | wc -l

# Redirecionamento para leitura e escrita
echo "teste fd" > /tmp/msh_fd_test && cat < /tmp/msh_fd_test && rm -f /tmp/msh_fd_test

# Criação e truncamento múltiplo
echo "um" > /tmp/fd1 > /tmp/fd2
echo "dois" >> /tmp/fd1 >> /tmp/fd2
cat /tmp/fd1 /tmp/fd2
rm -f /tmp/fd1 /tmp/fd2

# Pipes com comandos inválidos
ls | naoexiste | wc -l

# =======================================
# EXIT STATUS / PIPELINES
# =======================================

false | true
echo $?

true | false
echo $?

ls inexistente 2>/dev/null | grep x
echo $?

# =======================================
# SIGNALS
# =======================================

# Ctrl-C no prompt (não deve fechar o shell, só imprimir nova linha)
# (precisa ser testado manual: rode minishell, dê Ctrl-C, veja comportamento)

# Ctrl-\ no prompt (não deve matar o minishell)
# (manual também: rode e digite Ctrl-\)

# Ctrl-D no prompt (EOF) -> minishell deve sair limpo
# (manual: rode minishell e dê Ctrl-D)

# Ctrl-C em heredoc (não deve criar arquivo nem travar)
cat << STOP
linha1
^C
STOP

# =======================================
# ZOMBIE TEST (manual)
# =======================================
# Roda um comando em background & e verifica se não sobra zumbi
# minishell não precisa suportar jobs, mas não pode deixar processos sem waitpid()
# Testar: sleep 1 &
