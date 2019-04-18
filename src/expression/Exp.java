package expression;
import java.rmi.server.ExportException;
import java.util.EmptyStackException;
import java.util.Stack;
/**
 * 用来计算 表达式的值
 *@author liubailin
 * @note 这个类可随便引用和修改,但请说明出处
 */
public class Exp {
	private String sexp = null;

	private int Pexp = 0;
	private String PriorValue = "";
	private String ThisValue = "";

	private String lastexp = null;

	public Exp(String sexp) {
		this.sexp = "@" + sexp + "#";
	}

	public Exp(String exp, int t) {
		this.lastexp = exp;
	}
	
	public Exp() {
		this("@#");
	}

	public boolean isValid(){
		Pexp = 0;
		String last = "";
		String tmp = "";
		int is = 0;
		sexpNext();
		while(!( tmp=sexpNext() ).equals("#")){
				if(issingle(priorValidPexp(Pexp)) || tmp.equals(")") || tmp.equals("(") || tmp.equals(" ") )
					continue;
				else
					is = (is+1)%2;
				last = tmp;
				if(is == 1 && !canToNmb(tmp) ) return false;
				if(is == 0 && !issign(priorValidPexp(Pexp))) return false;
		}
		if(last.length() > 0 && !isNmb(last.charAt(tmp.length()-1) ) ) return false;
		Pexp = 0;
		return true;
	}
	
	private boolean isNmb(char a) {
		if( (a >= '0' && a <= '9') || a == '.')
			return true;
		else
			return false;
	}
	
	@Deprecated
	private boolean issign(int P){
		char a = sexp.charAt(P);
		if(isNmb(a) || (a >= 65 && a <= 90) || (a >= 97 && a <= 122))
			return false;
		else
			return true;
	}
	
	private boolean issingle(int Pexp){
		
		if(!issign(Pexp) && !isNmb(sexp.charAt(Pexp)) ) return true;
		
		if( sexp.charAt(Pexp) == '-'  && ( Pexp == 0 || (sexp.charAt(priorValidPexp(Pexp)) != ')'))) {
			 if(! isNmb(sexp.charAt(priorValidPexp(Pexp))) ) return true;
		}
		return false;
	}

	private String sexpNext(){
		String tmp = "";
		
		PriorValue = ThisValue;
		
		while(Pexp < sexp.length()-1 && sexp.charAt(Pexp) == ' ') Pexp ++;
		if(Pexp < sexp.length())
		do{
			tmp = tmp + sexp.charAt(Pexp);
			Pexp ++;
		}
		while( Pexp < sexp.length() && !issign(Pexp-1) && !issign(Pexp) );
		
		ThisValue = tmp;
		return tmp;
	}

	@Deprecated
	private int priorValidPexp(int Pexp){
		int P = Pexp;
		if(P == 0) return -1;
		while(sexp.charAt(--P) == ' ');
		return P;
	}

	private int level(String sign){
		int l = -256;		
		
		if(!isNmb(sign.charAt(0)) ) l = 127;

		switch(sign.charAt(0)){
		case '+' :
		case '-' :
			l = 10;
			break;
		case '*' :
		case '/' :
			l = 11;
			break;
		case '(' :
		case ')' :
			l = 128;
			break;
		case '$' :
			l = 127;
			break;
		case '[' :
			l = 1;
			break;
		case '#':
			l = -1;
			break;
		case '@':
			l = -2;
			break;
		}

		return l;
	}


	public double lexptoValue() throws ExpException,NumberFormatException{
		double result = 0;
		Stack<Double> nmb = new Stack<Double>();
		int p = 0;
		double tmpnmb = 0;
		String tmp = new String("");
		for(p = 0; p < lastexp.length(); p++){
			if(lastexp.charAt(p) == ' '){
			 
				switch(tmp.charAt(tmp.length()-1)){
				case '*':
					result = UseBigDecimal.multiply( nmb.pop().doubleValue(), nmb.pop().doubleValue());
					nmb.push(result);
					tmp = "";
					break;
				case '/':
					tmpnmb = nmb.pop();
					result = UseBigDecimal.divide((nmb.pop().doubleValue()), tmpnmb);
					nmb.push(result);
					tmp = "";
					break;
				case '+':
					result = UseBigDecimal.add(nmb.pop().doubleValue() ,nmb.pop());
					nmb.push(result);
					tmp = "";
					break;
				case '-':
					tmpnmb = nmb.pop();
					result = UseBigDecimal.subtract(nmb.pop().doubleValue(), tmpnmb);
					nmb.push(result);
					tmp = "";
					break;
				case '$':
					tmpnmb = nmb.pop();
					result = - tmpnmb;
					nmb.push(result);
					tmp = "";
					break;
				default:
					if(tmp.equals("sin"))
					{
						tmpnmb = nmb.pop();
						result = Math.sin(tmpnmb);
						nmb.push(result);
					}
					else if(tmp.equals("cos"))
					{
						tmpnmb = nmb.pop();
						result = Math.cos(tmpnmb);
						nmb.push(result);
					}
					else if(tmp.equals("tan"))
					{
						tmpnmb = nmb.pop();
						result = Math.tan(tmpnmb);
						nmb.push(result);
					}
					else if(tmp.equals("sqrt"))
					{
						tmpnmb = nmb.pop();
						result = Math.sqrt(tmpnmb);
						nmb.push(result);
					}
					else if(tmp.equals("log"))
					{
						tmpnmb = nmb.pop();
						result = Math.log10(tmpnmb);
						nmb.push(result);
					}
					else
						nmb.push(Double.valueOf(tmp));
					
					tmp = "";
				}
			}
			else
				tmp = tmp + (char) lastexp.charAt(p);
		}
		if(nmb.isEmpty()) throw new ExpException("Exp:NULL");
		double endresult = nmb.pop();
		if(!nmb.isEmpty()) throw new ExpException("++++++++++++++++");
		return endresult;
	}
	
	private boolean canToNmb(String strnmb){
		
		try{
			Double.valueOf(strnmb);
		}catch(Exception e){
			return false;
		}
		
		return true;		
	}

	public void stolast() throws ExpException{
		Pexp = 0;
		PriorValue = "";
		ThisValue = "";
		String out = "";
		String tmp = "";
			
		if(!this.isValid()) throw new ExpException("express is not valid ");

		Stack<String> sign = new Stack<String>();
		tmp = sexpNext();
		sign.push(tmp);
		
		while(!(tmp = sexpNext()).equals("")){
 
			if(canToNmb(tmp) ) {
				out = out + tmp + " ";
			}
			else
			{
				if(issingle(priorValidPexp(Pexp)) ) {
					if( tmp.equals("-"))	
						tmp = "$";
					
					while(level( sign.peek() ) > level( tmp ) ){
						out = out + sign.pop() + " ";
					}
					
					
					
				}
				else{
					
					while(level( sign.peek() ) >= level( tmp ) ){
						out = out + sign.pop() + " ";
					}
					
				}
				
				if( tmp.equals("(") ) 
					sign.push("[");
				else if(tmp.equals(")")){	
					String t = "";
					try {
						while(! ((t = sign.pop()).equals("[")) ){
							out = out + t +" ";
						}
					}catch(EmptyStackException e) {
						throw new ExpException("bracket can't match");
					}
					
				}
				else if(issingle(priorValidPexp(Pexp)) && sexp.charAt(priorValidPexp(Pexp)) == '-')
					sign.push("$");
				else
					sign.push(tmp);
			}

		}
		lastexp = out;
	}

	public String getlastexp(){
		return lastexp;
	}

}
