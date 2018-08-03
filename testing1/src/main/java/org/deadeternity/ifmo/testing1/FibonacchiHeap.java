package org.deadeternity.ifmo.testing1;

public class FibonacchiHeap {
    private FibonacchiHeapNode min;
    private int roots;

    public void addNode(FibonacchiHeapNode node) {
        if(roots == 0) {
            node.setLeft(node);
            node.setRight(node);
            this.min = node;
            roots++;
            return;
        } else if(roots == 1) {
            min.setLeft(node);
            min.setRight(node);
            node.setRight(min);
            node.setLeft(min);
        } else {
            FibonacchiHeapNode leftNode = min.getLeft();
            min.setLeft(node);
            node.setLeft(leftNode);
            node.setRight(min);
            leftNode.setRight(node);
        }
        if(min.getKey() > node.getKey()) min = node;
        roots++;
    }

    public FibonacchiHeapNode getMin() {
        return min;
    }

    public void union(FibonacchiHeap heap) {
        if(roots == 0) {
            this.addNode(heap.getMin());
            return;
        }
        if(heap.roots == 0) return;
        else {
            FibonacchiHeapNode originalLeftNode = min.getLeft();
            originalLeftNode.setRight(heap.min);
            min.setLeft(heap.min.getLeft());
            heap.min.getLeft().setRight(min);
            heap.min.setLeft(originalLeftNode);
            roots += heap.roots;
        }
        if(heap.min.getKey() < min.getKey()) min = heap.min;
    }

    private void consolidate() {
        FibonacchiHeapNode[] A = new FibonacchiHeapNode[this.roots];

        FibonacchiHeapNode cur = min;
        //compare cur with start to stop
        FibonacchiHeapNode start = min;
        do {
            int degree = cur.getDegree();
            //here's no root with same degree
            if(A[degree] == null) {
                A[degree] = cur;
            } else {
                //conflict, root with same degree found
                while(A[degree] != null || A[degree] == cur) {
                    //root from array
                    FibonacchiHeapNode conflictNode = A[degree];
                    //swap and child if cur > conflict root
                    if(cur.getKey() > conflictNode.getKey()) {
                        //swap
                        cur.swap(conflictNode);
                        System.out.println(this.toString());
                        //exclude from roots
                        cur.dropLinks();
                        this.roots--;
                        //set child
                        conflictNode.setChild(cur);
                        System.out.println(this.toString());

                        if(min == cur) min = conflictNode;
                        cur = conflictNode;

                        A[degree] = null;
                        degree = cur.getDegree();
                    } else {
                        if(start == conflictNode) start = cur;
                        conflictNode.dropLinks();
                        roots--;
                        cur.setChild(conflictNode);

                        A[degree] = null;
                        degree = cur.getDegree();
                    }
                }

                A[cur.getDegree()] = cur;
            }
            cur = cur.getRight();
        } while(cur != start);
        for (FibonacchiHeapNode node : A) {
            if(node != null && node.getKey() < this.min.getKey()) this.min = node;
        }
    }

    public void removeMin() {
        if(roots == 0) return;
        if(min.getDegree() == 0) {
            if(roots > 1) {
                FibonacchiHeapNode right = min.getRight();
                min.dropLinks();
                min = right;
                roots--;
            } else {
                min = null;
                roots = 0;
            }
        } else {
            FibonacchiHeapNode child = min.getChild();
            FibonacchiHeapNode cur = min.getChild();
            do {
                cur.setParent(null);
                cur = cur.getLeft();
                roots++;
            } while(cur != child);

            if(roots > 1) {
                child.getLeft().setRight(min.getRight());
                min.getRight().setLeft(child.getLeft());
                child.setLeft(min.getLeft());
                min.getLeft().setRight(child);

                min = min.getRight();
            } else {
                min = child;
            }

            roots--;
        }

        //consolidate
        this.consolidate();

    }

    @Override
    public String toString(){
        StringBuilder result = new StringBuilder();
        FibonacchiHeapNode cur = this.min;
        result.append("(");
        do {
            result.append(cur.getKey());
            if(cur.getDegree() != 0) {
                FibonacchiHeap nestedHeap = new FibonacchiHeap();
                nestedHeap.addNode(cur.getChild());
                result.append(nestedHeap.toString());
            }
            result.append(", ");
            cur = cur.getRight();
        }
        while(cur != this.min);
        result.append(")");

        return  result.toString();
    }
}
