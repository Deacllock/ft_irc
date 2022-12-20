#ifndef COMMANDS
# define COMMANDS

# include <string>
# include <vector>

class Command
{
	public:
		/* CONSTRUCTORS */
		Command() {}
		Command(std::string &str) {split_str(str);}
		Command(const Command &rhs)
		{
			if (this == &cmd) {return;}
			this->_cmd = rhs.getCmd();
			this->_params = rhs.getParams();
		}
		~Command() {}

		Command &operator=(const Command &rhs)
		{
			if (this == &cmd) {return;}
			this->_cmd = rhs.getCmd();
			this->_params = rhs.getParams();
			return *this;
		}

		/* GETTER */
		std::string &getCmd() const {return this->_cmd;}
		std::vector<std::string> &getParams() const {return this->_params;}

		/* SETTER */
		void	setCmd(std::string &cmd) {this->_cmd = cmd;}
		void	setParams(std::vector<std::string> &params) {this->_params = params;}

	private:
		std::string _cmd;
		std::vector<std::string> _params;

		/**
		 * Split string in command and parameters
		 * @param {String} str, the full command taken
		 * @return NULL
		 */
		 void	split_str(std::string &str)
		 {
		 }
};

#endif
