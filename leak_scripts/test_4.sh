# =======================
# REDIRECIONAMENTO SIMPLES
# =======================
echo "linha1" > out1.txt
echo "linha2" >> out1.txt
cat < out1.txt

# =======================
# REDIRECIONAMENTO ERRADO
# =======================
> arquivo_inexistente/nao_pode
echo $?   # deve ser != 0

# =======================
# PIPE SIMPLES
# =======================
echo "abc" | cat
echo "123" | grep 2
ls | wc -l

# =======================
# PIPE COM REDIRECIONAMENTO
# =======================
echo "xpto" | tee out2.txt | cat
cat out2.txt

# =======================
# PIPE LONGO
# =======================
echo "42 minishell" | tr ' ' '\n' | sort | uniq | wc -l

# =======================
# ERRO EM PIPE
# =======================
naoexiste | echo "deve rodar mesmo assim"
echo $?

# =======================
# FILE DESCRIPTORS
# =======================
echo "fd test" 1>fd_ok.txt
cat fd_ok.txt