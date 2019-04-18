package expression;

public class ExpException extends Exception{
	private static final long serialVersionUID = 2L;
	public ExpException(){
		this("表达式异常");
	}
	public ExpException(String msg){
		super(msg);
	}

}
