public class Eggs extends Food {
    private String quantity;

    public Eggs(String quantity)
    {
        super("Яйца");
        this.quantity = quantity;
    }

    public void consume() {
        System.out.println(this + " съедено");
    }

    public String getQuantity() {
        return quantity;
    }

    public void setQuantity(String quantity) {
        this.quantity = quantity;
    }

    public boolean equals(Object arg0) {
        if (super.equals(arg0)) {
            if (!(arg0 instanceof Eggs)) return false;
            return quantity.equals(((Eggs) arg0).quantity);
        } else
            return false;
    }

    @Override
    public String toString() {
        return super.toString() + " в количестве '" + quantity.toUpperCase() + "'";
    }
}