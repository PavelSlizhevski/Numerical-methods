public class Cheese extends Food {

    public Cheese()
    {
        super("Сыр");
    }

    public void consume() {
        System.out.println(this + " съеден");
    }

    @Override
    public boolean equals(Object arg0) {
        if (super.equals(arg0)) {
            if (!(arg0 instanceof Cheese)) return false;
            return true;
        } else
            return false;
    }

    @Override
    public String toString() {
        return super.toString();
    }
}