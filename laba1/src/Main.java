public class Main {

    //@SuppressWarnings("unchecked")
    public static void main(String[] args) {

        Food[] breakfast = new Food[20];

        int itemsSoFar = 0;
        for (String arg: args) {
            String[] parts = arg.split("/");
            switch (parts[0]) {
                case "Cheese" : {
                    breakfast[itemsSoFar] = new Cheese();
                    break;
                }
                case "Apple" : {
                    breakfast[itemsSoFar] = new Apple(parts[1]);
                    break;
                }
                case "Eggs" : {
                    breakfast[itemsSoFar] = new Eggs(parts[1]);
                    break;
                }
                default : {
                    break;
                }
            }
            itemsSoFar++;
        }

        for (Food food : breakfast) {
            if (food == null) break;
            food.consume();
        }


        int qauntityEggs = 0;
        for (Food food : breakfast) {
            if (food instanceof Eggs) {
                qauntityEggs += Integer.parseInt(((Eggs) food).getQuantity());;
            }
        }
        System.out.println("На завтрак мы съели " + qauntityEggs + " яиц");

        int EggsX2 = 0;
        Eggs eggsSearchingX2 = new Eggs("2");
        for (Food eggs : breakfast) {
            if (eggs instanceof Eggs) {
                if ((eggs).equals(eggsSearchingX2)) {
                    EggsX2++;
                }
            }
        }
        System.out.println("Количество порций с двумя яйцами " + EggsX2);
    }
}
