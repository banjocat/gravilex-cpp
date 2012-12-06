
/* If DEBUG is defined it will enter debug mode for that specific file.
 */


#ifdef DEBUG
#define debug(a) std::cerr << __FILE__ << ":" << __LINE__ << "-> " << a << std::endl
#else
#define debug(a) // std::cerr << __FILE__ << ":" << __LINE__ << "-> " << a << endl
#endif
