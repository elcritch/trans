import os, sys
##args grammar.txt

grammar = {}
right = {}
order = []
PostFix = '_1'

def parse(name):
    global grammar, right
    
    for line in fl:
        line = line.strip()
        if not line: continue

        prod = [ l.strip() for l in line.split(':') ]
        nt, prod = prod
        order.append(nt)
        grammar[nt] = [prod.split()]
        
        for line in fl:
            line = line.strip()
            if not line: break

            prod = line.split()
            if len(prod) == 1:
                prod.append(' ')
            
            # print "\tprod:",prod
            grammar[nt].append( prod[1:] )

def process():
    global grammar, right
    
    for i, rule in enumerate(order):
        prods = grammar[rule]
        rule_ = rule+PostFix
        
        # for 
        
        # eliminate immediate left recursion
        leftrec = [ p for p in prods if p[0]==rule]
        if leftrec:
            terms = [ p for p in prods if p[0] != rule ]
            right[rule] = [ t+[rule_] for t in terms ]
            right[rule_] = [ p[1:]+[rule_] for p in leftrec ]
            right[rule_].append([' '])
        else:
            right[rule] = grammar[rule]
            
        
    parse("grammar.txt")

def pprint(r):
    print r.ljust(10), ":", 
    pr = right[r][:1]
    if pr:
        print ' '.join(pr[0])
        
    for p in right[r][1:]:
        print '|'.rjust(12), ' '.join(p)
        
if __name__ == '__main__':

    fl = sys.stdin if not sys.argv[1:] else open(sys.argv[1],'r')
    
    parse(fl)
    process()
    
    reduced = [ g for g in right if g.endswith(PostFix) ]
    for r in order:
        r_ = r+PostFix
        pprint(r)
        print 
        
        if right.get(r_):
            pprint(r_)
        
        print
        


