

import java.util.Scanner;

import expression.Exp;
import expression.ExpException;

public class Example {
    public static void main(String[] args) {
        /**
         * 要计算表达式请分3步
         */
    	Scanner s = new Scanner(System.in);
    	String str = s.nextLine();
            // 1 . new Exp对像
        Exp ex = new Exp(str);
        try {

            //2. 调用这个方法(为什么要调用,可以不用管)
            ex.stolast();

            //3. 得出答案
            Double result = ex.lexptoValue();

            System.out.println(result);

        } catch (ExpException e){
            //这里处理表达式异常:提示用户
        	System.out.println(e.getMessage());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
