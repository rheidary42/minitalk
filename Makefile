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
CFLAGS  := -g -I.
# -Wall -Wextra -Werror 

SERVER  := server
CLIENT  := client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER).c
	@$(CC) $(CFLAGS) $(SERVER).c -o $(SERVER)
	@echo "$(GREEN)╔═══════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║   $(ORANGE)🎉 server      $(YELLOW)created 🎉$(GREEN)   ║$(RESET)"
	@echo "$(GREEN)╚═══════════════════════════════╝$(RESET)"

$(CLIENT): $(CLIENT).c
	@$(CC) $(CFLAGS) $(CLIENT).c -o $(CLIENT)
	@echo "$(GREEN)╔═══════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║   $(ORANGE)🎉 client      $(YELLOW)created 🎉$(GREEN)   ║$(RESET)"
	@echo "$(GREEN)╚═══════════════════════════════╝$(RESET)"

# --- cleaning ---

c:
	@rm -f $(SERVER)
	@rm -f $(CLIENT)
	@echo "$(RED)╔═══════════════════════════════╗$(RESET)"
	@echo "$(RED)║   $(RED)💀 server      removed 💀$(RED)   ║$(RESET)"
	@echo "$(RED)║   $(RED)💀 client      removed 💀$(RED)   ║$(RESET)"
	@echo "$(RED)╚═══════════════════════════════╝$(RESET)"
	@echo ""

re: c all
	@echo "$(CYAN)╔═══════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║   $(YELLOW)🔄   project rebuilt   🔄$(CYAN)   ║$(RESET)"
	@echo "$(CYAN)╚═══════════════════════════════╝$(RESET)"
	@echo ""

.PHONY: all c re