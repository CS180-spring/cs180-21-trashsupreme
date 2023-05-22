<script lang="ts">
import { defineComponent } from 'vue';
import EditableCell from './EditableCell.vue';
import AddButton from '../General_Components/AddButton.vue';
import DeleteButton from '../General_Components/DeleteButton.vue'

type TableItem = {
    content: string, row: number, column: number
}

function makeTable(content: string, delimiter: string) {
    let rows = content.split('\n')
    let table: TableItem[][] = []
    for (let row = 0; row < rows.length; row++) {
        //console.log(rows[row].trim())
        let contents = rows[row].trim().split(delimiter)
        table.push([])
        for (let column = 0; column < contents.length; column++) {
            table[table.length - 1].push({content: contents[column], row: row, column: column})
        }
    }
    return table
}

function condenseTable(table: TableItem[][], delimiter: string) {
    let res = ''
    for (let row = 0; row < table.length; row++) {
        for (let column = 0; column < table[row].length; column++) {
            res += table[row][column].content + delimiter
        }
        res = res.slice(0, res.length - 1)
        res += '\n'
    }
    res = res.slice(0, res.length - 1)
    return res
}

    export default defineComponent ({
        data() {return {
            display: [[{content: '', row: 0, column: 0}]],
            row: 0,
            column: 0
        }},
        props: {
            content: String,
            delimiter: String
        },
        components: {
            EditableCell,
            AddButton,
            DeleteButton
        },
        created() {
            if (this.content != null && this.delimiter != null) {
                this.display = makeTable(this.content, this.delimiter)
            } 
        },
        emits: ['submit'],
        methods: {
            submit(newVal: string = '', item: TableItem | null = null) {
                if (item != null) {
                    this.display[item.row][item.column].content = newVal
                }
                if (this.delimiter != null) {
                    this.$emit('submit', condenseTable(this.display, this.delimiter))
                }
            },
            addCell(item: TableItem) {
                this.display[item.row].splice(item.column, 0, {content: 'new item', row: item.row, column: 0})
                if (this.delimiter != null) {
                    let res = condenseTable(this.display, this.delimiter) //convert table to string
                    this.display = makeTable(res, this.delimiter) //remake table to recalculate indexes
                    this.$forceUpdate()
                    this.submit()
                }
            },
            deleteCell(item: TableItem) {
                this.display[item.row].splice(item.column, 1)
                this.submit()
            },
            addRow(item: TableItem) {
                this.display.splice(item.row, 0, [])
                this.addCell({content: 'new item', row: item.row, column: 0})
            },
            deleteRow(item: TableItem) {
                this.display.splice(item.row, 1)
                this.submit()
            }
        }
    })
</script>

<template>
    <div v-for="row in display">
        <span v-for="item in row">
            <EditableCell 
                :content="item.content"
                @submit="(newVal) => submit(newVal, item)"
                @add-cell="addCell(item)"
                @delete-cell="deleteCell(item)"
            />
        </span>
        <AddButton @click="addRow(row[0])"/><DeleteButton @click="deleteRow(row[0])"/>
    </div>
</template>

<style>

</style>