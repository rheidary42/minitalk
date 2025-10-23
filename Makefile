# --- colors ---

RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
CYAN    := \033[0;36m
ORANGE  := \033[38;5;214m
RESET   := \033[0m
BOLD    := \033[1m

# --- config ---

CC      := cc
CFLAGS  := -g -I./ft_printf -Wall -Wextra -Werror

SERVER  := server
CLIENT  := client

FT_PRINTF := ft_printf/libftprintf.a

all: $(SERVER) $(CLIENT) $(FT_PRINTF)

$(SERVER): $(SERVER).c $(FT_PRINTF)
	@$(CC) $(CFLAGS) $(SERVER).c $(FT_PRINTF) -o $(SERVER)
	@echo "$(GREEN)╔═══════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║   $(ORANGE)🎉 server      $(YELLOW)created 🎉$(GREEN)   ║$(RESET)"
	@echo "$(GREEN)╚═══════════════════════════════╝$(RESET)"

$(CLIENT): $(CLIENT).c $(FT_PRINTF)
	@$(CC) $(CFLAGS) $(CLIENT).c $(FT_PRINTF) -o $(CLIENT)
	@echo "$(GREEN)╔═══════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║   $(ORANGE)🎉 client      $(YELLOW)created 🎉$(GREEN)   ║$(RESET)"
	@echo "$(GREEN)╚═══════════════════════════════╝$(RESET)"
	@echo ""

# --- libraries ---

$(FT_PRINTF):
	@make -sC ft_printf
	@echo "$(GREEN)╔═══════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║   $(ORANGE)✅  printf.a $(YELLOW)  created ✅$(GREEN)   ║$(RESET)"
	@echo "$(GREEN)╚═══════════════════════════════╝$(RESET)"

# --- cleaning ---

c:
	@make clean -sC ft_printf
	@echo "$(RED)╔═══════════════════════════════╗$(RESET)"
	@echo "$(RED)║$(RED)💀 ft_printf objects removed 💀$(RED)║$(RESET)"
	@echo "$(RED)╚═══════════════════════════════╝$(RESET)"
	@echo ""

f:
	@make fclean -sC ft_printf
	@rm -f $(SERVER)
	@rm -f $(CLIENT)
	@echo "$(RED)╔═══════════════════════════════╗$(RESET)"
	@echo "$(RED)║$(RED)💀 ft_printf objects removed 💀$(RED)║$(RESET)"
	@echo "$(RED)║   $(RED)💀 server      removed 💀$(RED)   ║$(RESET)"
	@echo "$(RED)║   $(RED)💀 client      removed 💀$(RED)   ║$(RESET)"
	@echo "$(RED)╚═══════════════════════════════╝$(RESET)"
	@echo ""
	@make fclean -sC ft_printf
	@echo "$(RED)╔═══════════════════════════════╗$(RESET)"
	@echo "$(RED)║  $(RED) 💀 ft_printf.a removed 💀$(RED)   ║$(RESET)"
	@echo "$(RED)╚═══════════════════════════════╝$(RESET)"
	@echo ""


re: f all
	@echo "$(CYAN)╔═══════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║   $(YELLOW)🔄   project rebuilt   🔄$(CYAN)   ║$(RESET)"
	@echo "$(CYAN)╚═══════════════════════════════╝$(RESET)"
	@echo ""

.PHONY: all c f re