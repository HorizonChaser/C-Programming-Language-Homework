public class test {

    public static void main(String[] args) {
        String inRes = "1091111019911610212311212111610448110954911595115489511549109112108101125";
        String currChar;
        StringBuilder ans = new StringBuilder();
        int currPos = 0;
 
         try {
             while(inRes.length() > 0) {
                 currChar = inRes.substring(currPos, currPos+2);
                 if(Character.isLetter(Integer.parseInt(currChar)) || Character.isDigit(Integer.parseInt(currChar))) {
                     ans.append((char)(Integer.parseInt(currChar)));
                     inRes = inRes.substring(currPos+2);
                 }
                 else {
                     ans.append((char)(Integer.parseInt(inRes.substring(currPos, currPos + 3))));
                     inRes = inRes.substring(currPos+3);
                 }
             }
         } catch (Exception e) {
             e.printStackTrace();
         }
         System.out.print(ans);
    }
}