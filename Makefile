all:
	@$(MAKE) -C ./Source_code

run:
	@$(MAKE) run -C ./Source_code

clean:
	@$(MAKE) clean -C Source_code

fclean:
	@$(MAKE) fclean -C Source_code


finish:
	@$(MAKE) finish -C Source_code


re:	fclean all

.PHONY :	all clean fclean finish re run