typedef struct TreeStmt *TreeStmt;

struct TreeStmt {
  TokenCode code;
  union {
    struct {
      TreeLoc loc;
      TreeBool bool;
    } u_assign; 
    struct {
      TreeBool bool;
      TreeStmt stmt;
    } u_while; 
  } u;
};
