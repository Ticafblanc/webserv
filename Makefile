all:
	@$(MAKE) -C ./Source_code

run:
	@$(MAKE) run -C ./Source_code

test: all
	@./webserv www/all.conf
	@python3 Test/Tester.py

#pip install requests

clean:
	@$(MAKE) clean -C Source_code

fclean:
	@$(MAKE) fclean -C Source_code


finish:
	@$(MAKE) finish -C Source_code


re:	fclean all

.PHONY :	all clean fclean finish re run