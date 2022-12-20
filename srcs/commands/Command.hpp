#ifndef COMMANDS
# define COMMANDS

# include <string>
# include <vector>
# include <iostream>
# include <sstream>

class Command
{
	public:
		/* CONSTRUCTORS */
		Command() : _cmd(0), _params(0) {}
		Command(std::string &str) {split_str(str);}
		Command(const Command &rhs)
		{
			if (this == &rhs) {return;}
			this->_cmd = rhs.getCmd();
			this->_params = rhs.getParams();
		}
		~Command() {}

		Command &operator=(const Command &rhs)
		{
			if (this == &rhs) {return *this;}
			this->_cmd = rhs.getCmd();
			this->_params = rhs.getParams();
			return *this;
		}

		/* GETTER */
		std::string getCmd() const {return this->_cmd;}
		std::vector<std::string> getParams() const {return this->_params;}

		/* SETTER */
		void	setCmd(std::string &cmd) {this->_cmd = cmd;}
		void	setParams(std::vector<std::string> &params) {this->_params = params;}

	private:
		std::string _cmd;
		std::vector<std::string> _params;

		/**
		 * @brief Split string in command and parameters.
		 *
		 * @param str The full command taken
		 * @return VOID
		 */
		 void	split_str(std::string str)
		 {
		 	std::istringstream ss(str);
			std::string elem;

			bool first = true;
			while (getline(ss, elem, ' '))
			{
				if (first && elem != "")
				{
					this->_cmd = elem;
					first = false;
				}
				else if (elem != "")
					this->_params.push_back(elem);
			}
			// TEST
			/*std::cout << "CMD: {" << this->_cmd << "}" << std::endl;
			std::cout << "PARAMS:" << std::endl;
			std::vector<std::string>::iterator it = this->_params.begin();
			std::vector<std::string>::iterator it_end = this->_params.end();
			for (; it < it_end; it++)
				std::cout << "\t{" << *it << "}" << std::endl;*/
		 }
};

#endif
