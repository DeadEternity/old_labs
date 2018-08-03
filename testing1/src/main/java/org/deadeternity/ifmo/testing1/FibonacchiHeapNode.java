package org.deadeternity.ifmo.testing1;

public class FibonacchiHeapNode {
    private FibonacchiHeapNode parent;
    private FibonacchiHeapNode child;
    private FibonacchiHeapNode left;
    private FibonacchiHeapNode right;
    private int degree;
    private int key;

    public FibonacchiHeapNode getParent() {
        return parent;
    }

    public FibonacchiHeapNode getChild() {
        return child;
    }

    public FibonacchiHeapNode getLeft() {
        return left;
    }

    public FibonacchiHeapNode getRight() {
        return right;
    }

    public int getDegree() {
        return degree;
    }

    public int getKey() {
        return key;
    }

    public void setParent(FibonacchiHeapNode parent) {
        this.parent = parent;
    }

    public void setChild(FibonacchiHeapNode child) {
        if(this.getChild() == null) {
            child.setParent(this);
            child.setLeft(child);
            child.setRight(child);
            this.child = child;
            this.degree = child.getDegree() + 1;
        } else if(this.getChild().getRight() == this.getChild()) {
            FibonacchiHeapNode oldChild = this.getChild();
            FibonacchiHeapNode newChild = child;
            this.getChild().setLeft(newChild);
            this.getChild().setRight(newChild);
            child.setRight(oldChild);
            child.setLeft(oldChild);
            child.setParent(this);
            if(child.getDegree() + 1 > this.getDegree()) this.degree = child.getDegree() + 1;
        } else {
            FibonacchiHeapNode oldChild = this.getChild();
            FibonacchiHeapNode oldChildLeft = this.getChild().getLeft();
            oldChildLeft.setRight(child);
            child.setLeft(oldChildLeft);
            oldChild.setLeft(child);
            child.setRight(oldChild);
            child.setParent(this);
            if(child.getDegree() + 1 > this.getDegree()) this.degree = child.getDegree() + 1;
        }
    }

    public void setLeft(FibonacchiHeapNode left) {
        this.left = left;
    }

    public void setRight(FibonacchiHeapNode right) {
        this.right = right;
    }

    public void setDegree(int degree) {
        this.degree = degree;
    }

    public FibonacchiHeapNode(int key) {
        this.key = key;
        this.parent = null;
        this.child = null;
        this.right = null;
        this.left = null;
        this.degree = 0;
    }

    public void dropLinks() {
        if(this == this.getRight()) {
            this.setRight(null);
            this.setLeft(null);
        } else {
            FibonacchiHeapNode leftNode = this.getLeft();
            FibonacchiHeapNode rigthNode = this.getRight();
            leftNode.setRight(rigthNode);
            rigthNode.setLeft(leftNode);

            this.setLeft(null);
            this.setRight(null);
        }
    }

    public void swap(FibonacchiHeapNode swapNode) {
        if(this.getLeft() != swapNode && this.getRight() != swapNode) {
            FibonacchiHeapNode origLeft = this.getLeft();
            FibonacchiHeapNode origRight = this.getRight();
            FibonacchiHeapNode newLeft = swapNode.getLeft();
            FibonacchiHeapNode newRight = swapNode.getRight();

            origLeft.setRight(swapNode);
            origRight.setLeft(swapNode);
            newLeft.setRight(this);
            newRight.setLeft(this);

            swapNode.setRight(origRight);
            swapNode.setLeft(origLeft);
            this.setRight(newRight);
            this.setLeft(newLeft);
        } else if(this.getRight() == swapNode && this.getLeft() != swapNode) {
            FibonacchiHeapNode swapRight = swapNode.getRight();
            FibonacchiHeapNode origLeft = this.getLeft();

            swapRight.setLeft(this);
            origLeft.setRight(swapNode);

            swapNode.setLeft(origLeft);
            swapNode.setRight(this);
            this.setLeft(swapNode);
            this.setRight(swapRight);


        } else if(this.getLeft() == swapNode && this.getRight() != swapNode) {
            FibonacchiHeapNode swapLeft = swapNode.getLeft();
            FibonacchiHeapNode origRight = this.getRight();

            swapLeft.setRight(this);
            origRight.setLeft(swapNode);

            swapNode.setRight(origRight);
            swapNode.setLeft(this);
            this.setRight(swapNode);
            this.setLeft(swapLeft);

        } else return;
    }

    @Override
    public String toString() {
        return (new Integer(this.key).toString());
    }
}
